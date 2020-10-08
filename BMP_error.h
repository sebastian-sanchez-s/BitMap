void BMP_perror(const char * errmsg)
{
    fprintf(stderr, "Error: %s", errmsg);
    if (errno)
    {
        fprintf(stderr, "\nstrerror: %s", strerror(errno)); 
    }
    exit(1);
}
