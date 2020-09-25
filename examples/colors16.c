#include "../BMP.c"

int main() {
    int height = 200;
    int width = 200;
    struct BMP * image = BMP_create(height, width, 16, DIB_BITMAPINFOHEADER);

    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            struct Color16 color = {0};

            if (col > width/2 && row > height/2) {
                color.green = MAX_COLOR16;
            }
            else if (col > width/2) {
                color.red = MAX_COLOR16;
            }
            else if (row > height/2) {
                color.blue = MAX_COLOR16;
            }
            else 
            {
                color.red = color.green = color.blue = MAX_COLOR16;
            }
            
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }

    BMP_save(image, "colors16.bmp");
    return 0;
}
