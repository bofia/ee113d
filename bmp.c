#include <stdio.h>
#include <stdlib.h>
#include "ee113d.h"
#include "bmp.h"

// RGB weights for grayscale conversion
#define GRAYSCALE_R 0.2989
#define GRAYSCALE_G 0.5870
#define GRAYSCALE_B 0.1140


float* loadBitmapFileGrayscaleOutput(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, bool grayScaleInput) {
    FILE *filePtr; // our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header

    unsigned char* bitmapImage;
    float*         grayBitmapImage;

    int i, invertedI, h, w, rowOffset, paddingBytes, valuesPerPixel;

    // if input image is grayscale
    valuesPerPixel = grayScaleInput ? 1 : 3;


    // open filename in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("File read error\n");
        return NULL;
    }

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42) {
        printf("Not bmp file\n");
        fclose(filePtr);
        return NULL;
    }

    // Read headers
    fseek(filePtr, 10, SEEK_SET);
    fread(&(bitmapFileHeader.bOffBits), sizeof(bitmapFileHeader.bOffBits), 1, filePtr);

    fseek(filePtr, 0x22, SEEK_SET);
    fread(&(bitmapInfoHeader->biSizeImage), sizeof(bitmapInfoHeader->biSizeImage), 1, filePtr);

    // Read Height
    fseek(filePtr, 0x16, SEEK_SET);
    fread(&(bitmapInfoHeader->biHeight), sizeof(bitmapInfoHeader->biHeight), 1, filePtr);

    // Read Width
    fseek(filePtr, 0x12, SEEK_SET);
    fread(&(bitmapInfoHeader->biWidth), sizeof(bitmapInfoHeader->biWidth), 1, filePtr);

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);


    // allocate memory for bitmap image data
    bitmapImage = (unsigned char*)malloc(sizeof(unsigned char) * bitmapInfoHeader->biSizeImage);

    if (bitmapImage == NULL) {
        printf("Memory allocation failure\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }


    // read in the bitmap image data
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        printf("Image data not read\n");
        fclose(filePtr);
        return NULL;
    }

    //close file and return bitmap image data
    fclose(filePtr);


    // unreverse row data, grayscale, and return array data as floats
    paddingBytes = (4 - (bitmapInfoHeader->biWidth * valuesPerPixel % 4)) % 4;
    rowOffset = 0;


    grayBitmapImage = (float*)malloc(sizeof(float) * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth);


    for (h = 0; h < bitmapInfoHeader->biHeight; h++) {
      for (w = 0; w < bitmapInfoHeader->biWidth; w++) {
        i = bitmapInfoHeader->biWidth * h + w;
        invertedI = bitmapInfoHeader->biWidth*(bitmapInfoHeader->biHeight-1-h) + w;

        // gbr -> rgb, grayscale, and normalize
        if (grayScaleInput) {
            grayBitmapImage[invertedI] = ((float)(bitmapImage[i + rowOffset])) / 255.0;
        }
        else {
            grayBitmapImage[invertedI] = (GRAYSCALE_R * (float)(bitmapImage[i*3 + rowOffset + 2]) +
                                          GRAYSCALE_G * (float)(bitmapImage[i*3 + rowOffset + 1]) +
                                          GRAYSCALE_B * (float)(bitmapImage[i*3 + rowOffset + 0])) / 255.0;
        }

      }
      rowOffset += paddingBytes;
    }

    free(bitmapImage);

    return grayBitmapImage;
}
