#include "../BMP.c"

int main() {
    struct BMP * image = BMP_create(255, 255, 24, 0);

    int height = BMP_getheight(image);
    int width = BMP_getwidth(image);

    struct Color24 color = {0};

    for (int row = height-1; row >= 0; row--) 
    {
        color.red++;

        for (int col = 0; col < width; col++) 
        {
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }   

    BMP_save(image, "red_gradient24.bmp");
    return 0;
}