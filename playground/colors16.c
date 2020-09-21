#include "../BMP.c"

int main() {
    struct _BMP * image = BMP_create(200, 200, 16, BITMAPINFOHEADER);
    
    int height = get_height(image);
    int width = get_width(image);

    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            struct Color16 color = {0};

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

    BMP_save(image, "colors16.bmp");
    return 0;
}
