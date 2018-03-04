#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include "stdio.h"
#include <math.h>

#define M_PI 3.14159265358979323846
#define W_PI 57.29577951308233


#define SHARPEN_LAP_0 0
#define SHARPEN_LAP_1 1
#define SHARPEN_LAP_2 2
#define SHARPEN_LAP_3 3

#define LAPLACE_MASK_SIZE 3
#define SOBEL_MASK_SIZE 3
#define ROBERT_MASK_SIZE 3

#define EDGE_DETECTOR_ROBERT 1
#define EDGE_DETECTOR_PREWITT 2
#define EDGE_DETECTOR_KIRSCH 3
#define EDGE_DETECTOR_SOBEL 4
#define EDGE_DETECTOR_LOG 5
#define EDGE_DETECTOR_DOG 6
#define EDGE_DETECTOR_LAPLACE 7
#define EDGE_DETECTOR_CANNY 8


#endif
