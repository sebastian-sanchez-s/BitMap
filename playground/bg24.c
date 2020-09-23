#include "../BMP.c"

int main()
{
    int height = 200;
    int width = 200;
    struct BMP * image = BMP_create(height, width, 24, 0);
    struct Color24 color = {MAX_COLOR24/3, MAX_COLOR24*2/3, MAX_COLOR24};

    BMP_set_background(image, (void *) &color);

    BMP_save(image, "bg24.bmp");
    return 0;
}
