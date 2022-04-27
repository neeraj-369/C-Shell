#include "headers.h"

void pwd()
{
    char getpath[100];
    getcwd(getpath, 100);
    printf("%s\n", getpath);
}