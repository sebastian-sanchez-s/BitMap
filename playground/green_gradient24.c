#include "../BMP.c"

int main() {
    struct _BMP * image = BMP_create(255, 255, 24, 0);

    int height = get_height(image);
    int width = get_width(image);

    struct Color24 color = {0};

    for (int row = height-1; row >= 0; row--) 
    {
        color.green++;

        for (int col = 0; col < width; col++) 
        {
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }   

    BMP_save(image, "green_gradient24.bmp");
    return 0;
}
