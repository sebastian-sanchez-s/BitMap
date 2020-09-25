void BMP_perror(const char * errmsg)
{
    fprintf(stderr, "Error: %s", errmsg);
    fprintf(stderr, "\nStrerr: %s", strerr(errno)); 
    exit(1);
}
