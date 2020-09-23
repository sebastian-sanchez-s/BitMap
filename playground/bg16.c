#include "../BMP.c"

int main()
{
    int height = 200;
    int width = 200;
    struct BMP * image = BMP_create(height, width, 16, 0);
    struct Color16 color = {MAX_COLOR16/3, MAX_COLOR16*2/3, MAX_COLOR16};

    BMP_set_background(image, (void *) &color);

    BMP_save(image, "bg16.bmp");
    return 0;
}
