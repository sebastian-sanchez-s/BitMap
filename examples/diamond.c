#include "../BMP_utils.h"
#include <math.h>

int main() {
    struct BMP * img = BMP_create(200, 200, 24);

    const char black[] = {0, 0, 0};
    const char white[] = {255, 255, 255};

    int h = img -> infoheader.height;
    int w = img -> infoheader.width;
    // center of image
    int cx = w/2;
    int cy = h/2;
    int border = (cx + cy)/2;
    for (int row = h-1; row >= 0; row--)
    {
        for (int col = 0; col < w; col++)
        {
            if ( abs(cy - row) + abs(cx - col) < border)
            {
                BMP_set_pixel(img, row, col, white);
            }
            else
            {
                BMP_set_pixel(img, row, col, black);
            }
        }
    }

    BMP_save(img, "diamond.bmp");
        
    return 0;
}
