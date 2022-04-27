#include "headers.h"

void historyi(char *a)
{
    char *token;
    token = strtok(a, " ");
    token = strtok(NULL, " ");

    int size;

    for (size = 0; size < 20; size++)
    {
        if (strcmp(history[size], "") == 0)
            break;
    }

    if (token == NULL)
    {
        if (size <= 10)
        {
            for (int i = 0; i < size; i++)
            {

                printf("%s\n", history[i]);
            }
        }
        else
        {
            for (int i = size - 10; i < size; i++)
            {

                printf("%s\n", history[i]);
            }
        }
    }
    else
    {
        int sum = 0;
        int pow = 1;

        for (int i = strlen(token) - 1; i >= 0; i--)
        {
            int z = token[i] - 48;
            sum += z * pow;
            pow = pow * 10;
        }
        if (sum >= size)
        {
            for (int i = 0; i < size; i++)
            {
                printf("%s\n", history[i]);
            }
        }
        else
        {
            for (int i = size - sum; i < size; i++)
            {
                printf("%s\n", history[i]);
            }
        }
    }
}

void makehistory(char *a)
{
    int size;

    for (size = 0; size < 20; size++)
    {
        if (strcmp(history[size], "") == 0)
            break;
    }

    if (size < 20)
    {
        strcpy(history[size], a);
    }
    if (size == 20)
    {
        for (int i = 0; i < size - 1; i++)
        {
            strcpy(history[i], history[i + 1]);
        }
        strcpy(history[size - 1], a);
    }
}

void sendfiletohistory()
{
    int c = open("history.txt", O_CREAT | O_RDONLY, 0777);
    char buffer[10000];
    read(c, buffer, 10000);
    int i = 0;
    int k = 0;
    int j = 0;
    while (1)
    {
        if (buffer[i] == '\n' || buffer[i] == '\0')
        {
            history[k][j] = '\0';
            k++;
            j = 0;
        }
        else
        {
            history[k][j] = buffer[i];
            j++;
        }

        if (buffer[i] == '\0')
            break;
        i++;
    }
    close(c);
}

void sendhistorytofile()
{
    int c = open("history.txt", O_RDONLY | O_WRONLY | O_TRUNC, 0777);
    char buffer[10000];
    int j = 0;
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(history[i], "") == 0)
        {
            break;
        }
        for (int k = 0; k < strlen(history[i]); k++)
        {
            buffer[j] = history[i][k];
            j++;
        }
        buffer[j] = '\n';
        j++;
    }
    buffer[j - 1] = '\0';
    int s = write(c, buffer, strlen(buffer));
    close(c);
}