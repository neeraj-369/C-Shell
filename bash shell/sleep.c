#include "headers.h"

void sleepi(char *a)
{
    char c[1000];
    int i;
    strcpy(c, a);

    char *token = strtok(c, " ");
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        int time = 0;
        int pow = 1;

        for (int i = strlen(token) - 1; i >= 0; i--)
        {
            int b = token[i] - 48;
            time += b * pow;
            pow = pow * 10;
        }

        sleep(time);
    }
    else
    {
        printf("entire time in seconds\n");
    }
}