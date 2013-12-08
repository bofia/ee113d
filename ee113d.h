//
// ee113d.h
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#ifndef EE113D
#define EE113D

#ifndef DSK
#define DSK
#endif

typedef enum {
    false,
    true
} bool;

#define IMAGE_WIDTH    180
#define IMAGE_HEIGHT   200
#define IMAGE_SIZE     (IMAGE_WIDTH * IMAGE_HEIGHT)
#define NUM_IMAGES     32
#define NUM_EIGENFACES 20

#endif
// EE113D
