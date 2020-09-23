#include "../BMP.c"

int main() {
    struct BMP * image = BMP_create(7905, 7905, 16, 0);

    int height = BMP_get_height(image);
    int width = BMP_get_width(image);

    struct Color16 color = {0};

    for (int row = height-1; row >= 0; row--) 
    {
        if (row % 255 == 0)
        {
            color.green++;
        }

        for (int col = 0; col < width; col++) 
        {
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }   

    BMP_save(image, "green_gradient16.bmp");
    return 0;
}
