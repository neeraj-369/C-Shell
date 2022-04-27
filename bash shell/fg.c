#include "headers.h"

void fg(char *a)
{
    char c[1000];
    int i;
    strcpy(c, a);
    char *token = strtok(c, " ");

    int pid = fork();
    if (pid > 0)
    {
        wait(NULL);
    }
    if (pid == 0)
    {
        char *exec_args[] = {token, NULL};
        if (execvp(token, exec_args) == -1)
        {
            perror("No such executable process");
            exit(0);
        }
    }
}