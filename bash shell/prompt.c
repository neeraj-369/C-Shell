#include "headers.h"

void prompt()
{
    int j = 0;
    char hostname[101];
    gethostname(hostname, 101);
    char *username;
    username = getlogin();

    char getpath[100];
    getcwd(getpath, 100);

    if (strlen(getpath) >= strlen(initpath))
    {
        char pathipath[1000];
        strcpy(pathipath, getpath);
        pathipath[strlen(initpath)] = '\0';
        if (strcmp(pathipath, initpath) == 0)
        {
            strcpy(getpath, &getpath[strlen(initpath)]);
        }
    }

    printf("<%s@%s:~%s> ", username, hostname, getpath);
}
