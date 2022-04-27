#include "headers.h"

void cd(char *a)
{
    char c[1000];
    strcpy(c, a);
    char *token = strtok(c, " ");
    token = strtok(NULL, " ");
    if (token == NULL || strcmp(token, "~") == 0)
    {
        char path[1000];
        getcwd(path, 1000);
        strcpy(previouspath, path);
        chdir(getenv("HOME"));
    }
    else if (strcmp(token, "..") == 0)
    {
        char path[1000];
        getcwd(path, 1000);
        strcpy(previouspath, path);
        chdir("..");
    }
    else if (strcmp(token, "-") == 0)
    {
        chdir(previouspath);
    }
    else
    {
        char path[1000];
        getcwd(path, 1000);
        strcpy(previouspath, path);
        chdir(token);
    }
}