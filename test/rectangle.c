#include "../BMP_utils.h"

int main() {
    struct BMP * image = BMP_create(200, 200, 24);

    const char blue[] = {255, 0, 0};

    for (int row = image -> infoheader.height-1; row >= 0; row--)
    {
        for (int col = 0; col < image -> infoheader.width; col++)
        {
            BMP_set_pixel(image, row, col, blue); 
        }
    }

    BMP_save(image, "rectangle.bmp");
    return 0;
}
