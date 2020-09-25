#include "../BMP.c"

int main() {
    int height = 200;
    int width = 200;
    struct BMP * image = BMP_create(height, width, 24, DIB_BITMAPINFOHEADER);
    
    struct Color24 white = {MAX_COLOR24, MAX_COLOR24, MAX_COLOR24};
    BMP_set_background(image, (void *) &white);

    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            struct Color24 color = {0};

            if (col > width/2 && row > height/2) {
                color.green = MAX_COLOR24;
            }
            else if (col > width/2) {
                color.red = MAX_COLOR24;
            }
            else if (row > height/2) {
                color.blue = MAX_COLOR24;
            }
            
            BMP_set_pixel(image, row, col, (void *) &color);
        }
    }

    BMP_save(image, "colors24.bmp");
    return 0;
}
