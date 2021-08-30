#include "BMP.h"

int main() {
    int height = 512;
    int width = 512;
    
    struct BMP * image = BMP_create(width, height, 16, 0);
    
    struct Color color = {0};

    float ri, gi, bi = 0.25;

    for (int row = height-1; row >= 0; row--) {
        for (int col = 0; col < width; col++) {
            ri = (float)col / (height-1);
            gi = (float)row / (width-1);

            color.red = ri * MAX_COLOR_16;
            color.green = gi * MAX_COLOR_16;
            color.blue = 0.25 * MAX_COLOR_16;

            BMP_set_pixel(image, row, col, color);
        }
    }
    

    BMP_save(image, "colors_16.bmp");
    return 0;
}
