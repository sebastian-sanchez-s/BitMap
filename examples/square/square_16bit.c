#include "../../BMP.c" // looks awfull 

int main() {
    struct _BMP * image = BMP_create(200, 200, 16, BITMAPINFOHEADER);

    const char color[] = {255, 0, 0};

    int height = get_height(image);
    int width = get_width(image);
    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)   
        {
            BMP_set_pixel(image, row, col, color);
        }
    }

    BMP_save(image, "square_16bit.bmp");
    return 0;
}
