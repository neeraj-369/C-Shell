#include "headers.h"

void echo(char *a)
{
    char c[1000];
    int i;
    strcpy(c, a);

    char *token = strtok(c, " ");
    token = strtok(NULL, " ");

    while (token != NULL)
    {
        printf("%s ", token);
        token = strtok(NULL, " ");
    }

    printf("\n");
}