#include "../BMP.c"

int main() {
    struct BMP * image = BMP_create(200, 200, 24, DIB_BITMAPINFOHEADER);
    
    int height = BMP_get_height(image);
    int width = BMP_get_width(image);

    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            struct Color24 color = {0};

            if (col > width/2 && row > height/2) {
                color.green = 255;
            }
            else if (col > width/2) {
                color.red = 255;
            }
            else if (row > height/2) {
                color.blue = 255;
            }
            
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }

    BMP_save(image, "colors24.bmp");
    return 0;
}
