/*  Un algoritmo recursivo para dibujar una recta.
 *  Compilado con:
 *      gcc my_line.c -lm -o app
 *
 * */

#include "../BMP.c"
#include <math.h>


typedef struct {
    int y;
    int x;
} Tuple;

Tuple * new_tuple(int y, int x)
{
    Tuple * tuple = BMP_malloc(sizeof(Tuple *), "Cannot create tuple");
    tuple-> y = y;
    tuple-> x = x;

    return tuple;
}

int distance(Tuple * p1, Tuple * p2)
{
    return sqrt(pow(p1-> y - p2-> y, 2) + pow(p1-> x - p2-> x, 2));
}

Tuple * mid_point(Tuple * point1, Tuple * point2)
{
    return new_tuple((point1-> y + point2-> y)/2, (point1-> x + point2-> x)/2);
}

void print_tuple(Tuple * tuple)
{
    printf("(%i, %i)\n", tuple-> y, tuple-> x);
}

void draw_midpoint(struct BMP * image, Tuple * point1, Tuple * point2, struct Color color)
{
    if (distance(point1, point2) < 2)
    {
        return;
    }

    Tuple * mid = mid_point(point1, point2);

    printf("------\n"); 
    print_tuple(point1);
    print_tuple(point2);
    print_tuple(mid);

    int y = mid-> y > 0 ? mid-> y: BMP_get_height(image)/2 + mid-> y; 
    int x = mid-> x > 0 ? mid-> x: BMP_get_width(image)/2 + mid-> x;
    
    BMP_set_pixel(image, y, x, color);
    draw_midpoint(image, point1, mid, color);
    draw_midpoint(image, mid, point2, color);
}

int main(int argc, char * argv[])
{
    int height = 400, width = 400;
    int mid = height / 2;
    struct BMP * image = BMP_create(height, width, 16, 0);

    if (argc < 5)
    {
        BMP_perror("Usage: ./app <y1> <x1> <y2> <x2>");
    }

    struct Color grid = {MAX_COLOR_16/4, 0, 0};
    struct Color axis = {MAX_COLOR_16/2, 0, 0};
    int unit = 10;
    for (int row = height - 1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            if (col % unit == 0 || row % unit == 0)
            {
                BMP_set_pixel(image, row, col, grid);
            }
            if (col == mid || row == mid)
            {
                BMP_set_pixel(image, row, col, axis);
            }
        }
    }
    
    Tuple * point1 = new_tuple(mid + unit * atoi(argv[0]), mid + unit * atoi(argv[2]));
    Tuple * point2 = new_tuple(mid + unit * atoi(argv[3]), mid + unit * atoi(argv[4]));

    struct Color color = {0, 0, MAX_COLOR_16};
    draw_midpoint(image, point1, point2, color);

    BMP_save(image, "my_line.bmp");
    return 0;
}

