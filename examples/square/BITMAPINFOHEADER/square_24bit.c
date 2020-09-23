#include "../../../BMP.c" // looks awfull 

int main() {
    struct BMP * image = BMP_create(200, 200, 24, DIB_BITMAPINFOHEADER);

    struct Color24 color = {MAX_COLOR24, 0, 0}; // blue

    int height = get_height(image);
    int width = get_width(image);
    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)   
        {
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }

    BMP_save(image, "square_24bit.bmp");
    return 0;
}
