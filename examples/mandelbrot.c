#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "BMP.h"


double distance(int y1, int x1, int y2, int x2) {
    return sqrt(pow(abs(y1 - y2), 2) + pow(abs(x1 - x2), 2));
}

int main(int argc, char * argv[]) {
    int height = 1000;
    int width = 1000;

    struct BMP * complex_plane = BMP_create(height, width, 24, 0);
    struct Color color = {0};

    int max_iteration = 1000;
    complex z;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            complex c = ((-row + height / 2) / 100.0) * I + (col - width / 2) / 100.0; 
            z = argc == 2 ? atof(argv[1]): 0;
            z += argc == 3 ? atof(argv[2])*I: 0;

            color.red = color.blue = color.green = 0;

            for (int n = 0; n < max_iteration; n++) {
                if (cabs(z) > 2.0) {
                    if (n < max_iteration / 60) {
                        color.red = MAX_COLOR_24;
                    } else if (n < max_iteration / 30){
                        color.blue = MAX_COLOR_24;
                    } else {
                        color.green = MAX_COLOR_24;
                    }
                    break;    
                }
                
                z = z*z + c;
            }

            BMP_set_pixel(complex_plane, row, col, color);
        }
    }

    BMP_save(complex_plane, "mandelbrot.bmp");
    return 0;
}
