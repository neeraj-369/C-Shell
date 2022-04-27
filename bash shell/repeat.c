#include "headers.h"

void repeat(char *a)
{
    char c[1000];
    int i;
    strcpy(c, a);

    char *token = strtok(c, " ");
    token = strtok(NULL, " ");
    int sum = 0;
    int pow = 1;

    for (int i = strlen(token) - 1; i >= 0; i--)
    {
        int z = token[i] - 48;
        sum += z * pow;
        pow = pow * 10;
    }

    token = strtok(NULL, " ");

    for (int i = 0; i < sum; i++)
    {
        if (strcmp(token, "cd") == 0)
        {
            int j = 0;
            while (a[j] != 'c' || a[j + 1] != 'd')
                j++;
            cd(&a[j]);
        }

        if (strcmp(token, "echo") == 0)
        {
            int j = 0;
            while (a[j] != 'e' || a[j + 1] != 'c' || a[j + 2] != 'h' || a[j + 3] != 'o' || a[j + 4] != ' ')
                j++;
            echo(&a[j]);
        }

        if (strcmp(token, "pwd") == 0)
            pwd();

        if (strcmp(token, "ls") == 0)
        {
            int j = 0;
            while (a[j] != 'l' || a[j + 1] != 's' || a[j + 2] != ' ')
                j++;
            ls(&a[j]);
        }

        if (strcmp(token, "sleep") == 0)
        {
            int j = 0;
            while (a[j] != 's' || a[j + 1] != 'l' || a[j + 2] != 'e' || a[j + 3] != 'e' || a[j + 4] != 'p' || a[j + 5] != ' ')
                j++;
            sleepi(&a[j]);
        }

        if (strcmp(token, "pinfo") == 0)
        {
            int j = 0;
            while (a[j] != 'p' || a[j + 1] != 'i' || a[j + 2] != 'n' || a[j + 3] != 'f' || a[j + 4] != 'o')
                j++;
            pinfo(&a[j]);
        }

        if (strcmp(token, "history") == 0)
        {
            int j = 0;
            while (a[j] != 'h' || a[j + 1] != 'i' || a[j + 2] != 's' || a[j + 3] != 't' || a[j + 4] != 'o' || a[j + 5] != 'r' || a[j + 6] != 'y')
                j++;
            historyi(&a[j]);
        }
    }
}
