/************************************************
 * Compiled with:
 *  gcc palette_16.c -I../ -L../ -lbmp -o app *
 ************************************************/

#include "BMP.h"

int main() {
    int height = MAX_COLOR_16 * 3;
    int width = MAX_COLOR_16 * 3;
    
    struct BMP * image = BMP_create(width, height, 16, 0);
    
    struct Color color = {0};

    for (int row = 0; row < height; row++) {
        if (row < MAX_COLOR_16) {
            color.red++;
        } else if (row < 2 * MAX_COLOR_16) {
            color.red = 0;
            color.green++;
        } else {
            color.green = 0;
            color.blue++;
        }

        for (int col = 0; col < width; col++) {
            BMP_set_pixel(image, row, col, color);
        }
    }
    

    BMP_save(image, "palette_16.bmp");
    return 0;
}
