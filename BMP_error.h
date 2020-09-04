#include <stdlib.h> // exit()

void BMP_perror(const char * errmsg)
{
    fprintf(stderr, errmsg);
    exit(0);
}
