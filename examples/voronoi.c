#include "../BMP.c"
#include <time.h>
#include <math.h>

struct Vector2List {
    int y;
    int x;
    struct Vector2List * next;
    unsigned int curr_distance;
};

struct Vector2List * build_list(int length, int limy, int limx)
{
    struct Vector2List * points = malloc(sizeof(struct Vector2List *));
    struct Vector2List * head = points;
    srand(time(NULL));

    points -> x = rand() % limx;
    points -> y = rand() % limy;
    points -> next = NULL;
    for (int i = 0; i < length-1; i++)
    {
        points -> next = malloc(sizeof(struct Vector2List *));
        points = points -> next;

        if (!points)
        {
            BMP_perror("Malloc failed");
        }
        points -> x = rand() % limx;
        points -> y = rand() % limy;
        points -> next = NULL;
    }

    return head;
}

unsigned int distance(int y1, int x1, int y2, int x2)
{
    return sqrt(pow(x1 - x2, 2) +  pow(y1 - y2, 2));
}

int minimum_points(int row, int col, struct Vector2List * points)
{
    // get minimun distance
    unsigned int min_distance = 0;
    struct Vector2List * travel = points;
    while (travel)
    {
        travel -> curr_distance = distance(row, col, travel->y, travel->x);

        if (min_distance == 0 || travel -> curr_distance < min_distance)
        {
            min_distance = travel -> curr_distance;
        }

        travel = travel -> next;
    }

    // see how many points match
    int counter = 0;
    travel = points;
    while (travel)
    {
        if (travel -> curr_distance == min_distance)
        {
            counter++;
        }
        travel -> curr_distance = 0;
        travel = travel -> next;
    }

    return counter;
}

void destroy_list(struct Vector2List * points)
{
    while (points)
    {
        struct Vector2List * travel = points;
        points = points -> next;
        free(travel);
    }
}

int main(int argc, char * argv[])
{
    if (argc == 1)
    {
       BMP_perror("# points should be specified");
    } 

    int height = 500, width = 500;
    struct Color blue = {MAX_COLOR_16, 0, 0}; 
    struct Color white = {MAX_COLOR_16, MAX_COLOR_16, MAX_COLOR_16}; 
    struct Color black = {0, 0, 0}; 

    struct BMP * image = BMP_create(height, width, 16, 0);
    BMP_set_background(image, white);
    BMP_set_horizontal_resolution(image, 2000);
    BMP_set_vertical_resolution(image, 2000);
   

    // CENTER OF DIAGRAMS
    struct Vector2List * points = build_list(atoi(argv[1]), height, width);

    // DRAW POINTS
    struct Vector2List * travel = points;
    while (travel)
    {
        BMP_set_pixel(image, travel->y, travel->x, blue);
        BMP_set_pixel(image, travel->y+1, travel->x+1, blue);
        BMP_set_pixel(image, travel->y-1, travel->x+1, blue);
        BMP_set_pixel(image, travel->y+1, travel->x-1, blue);
        BMP_set_pixel(image, travel->y-1, travel->x-1, blue);

        travel = travel -> next;
    }

    // DRAW BORDERS O(H*W + N) (brute force)
    for (int row = height -1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            if (minimum_points(row, col, points) > 1)
            {
                BMP_set_pixel(image, row, col, black);
            }
        }
    }

    destroy_list(points);
    BMP_save(image, "voronoi.bmp");
    return 0;
}
