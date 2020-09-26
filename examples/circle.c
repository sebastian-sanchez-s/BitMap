/*
 *  Draw a cirle using bresenham's algorithm 
 *  and the BMP library
 *
 *  Compiled with:
 *          gcc circle.c -o app
 */

#include "../BMP.c"


void draw_circle(struct BMP * image, int centery, int centerx, int row, int col, struct Color color)
{
    BMP_set_pixel(image, centery + row, centerx + col, color);
    BMP_set_pixel(image, centery - row, centerx + col, color);
    BMP_set_pixel(image, centery + row, centerx - col, color);
    BMP_set_pixel(image, centery - row, centerx - col, color);
    BMP_set_pixel(image, centery + col, centerx + row, color);
    BMP_set_pixel(image, centery - col, centerx + row, color);
    BMP_set_pixel(image, centery + col, centerx - row, color);
    BMP_set_pixel(image, centery - col, centerx - row, color);

}


int main(int argc, char * argv[]) 
{
    // image properties
    int height = 1000;
    int width = 1000;
    int center = height/2;
    int resolution = 96*2000;

    // image creation
    struct BMP * image = BMP_create(height, width, 16, 0);

    BMP_set_horizontal_resolution(image, resolution);
    BMP_set_vertical_resolution(image, resolution);

    // grid
    struct Color grid = {MAX_COLOR_16/4, 0, 0};
    struct Color axes = {MAX_COLOR_16/2, 0, 0};
    int unit = 20;

    for (int row = height-1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            if ((row % unit == 0) || (col % unit == 0))
            {
                BMP_set_pixel(image, row, col, grid);
            }
            if ((row == height/2) || (col == width/2))
            {
                BMP_set_pixel(image, row, col, axes);
            }
        }
    }

    // draw circle
    struct Color circle_color = {0, 0, MAX_COLOR_16};
    int rad = 10 * unit;
    int d = 3 - (2 * rad);
    int y = rad, x = 0;
    int centerx = width/2, centery = height/2; 

    draw_circle(image, centery, centerx, y, x, circle_color);
    while (x < y) 
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x-y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        draw_circle(image, centery, centerx, y, x, circle_color);
    }
    

    BMP_save(image, "circle.bmp");
    return 0;
}
