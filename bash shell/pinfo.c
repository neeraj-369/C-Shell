#include "headers.h"

void pinfo(char *a)
{
    char c[1000];
    int i;
    strcpy(c, a);
    char *token = strtok(c, " ");
    char flag[100];
    token = strtok(NULL, " ");
    int x = 0;
    if (token == NULL)
        x = 1;
    else
        strcpy(flag, token);

    if (x == 1)
    {
        char filename[1000];
        sprintf(filename, "/proc/%d/stat", getpid());
        char exe[1000];
        sprintf(exe, "/proc/%d/exe", getpid());
        FILE *f = fopen(filename, "r");

        char data[1000];

        fscanf(f, "%[^\n]", data);

        char required[10][100];
        int j;
        char *tokeni = strtok(data, " ");
        for (j = 0; j < 9; j++)
        {
            strcpy(required[j], tokeni);
            tokeni = strtok(NULL, " ");
        }

        printf("pid -- %s\n", required[0]);
        if (strcmp(required[4], required[7]) == 0)
            printf("Process Status -- %s+\n", required[2]);
        else
            printf("Process Status -- %s\n", required[2]);
        printf("memory -- %s{Virtual Memory}\n", required[8]);
        char path[1000];
        int ret = readlink(exe, path, 1000);
        if (ret != -1)
            printf("Executable Path -- ~/%s\n", required[1]);
        else
            printf("no executable path\n");
        fclose(f);
    }
    else
    {
        char filename[1000];
        sprintf(filename, "/proc/%s/stat", flag);
        FILE *f; 
        if(!(f= fopen(filename, "r")))
        {
            perror("Error");
            return;
        }
        char exe[1000];
        sprintf(exe, "/proc/%s/exe", flag);
        char data[1000];

        fscanf(f, "%[^\n]", data);

        char required[10][100];
        int j;
        char *tokeni = strtok(data, " ");
        for (j = 0; j < 9; j++)
        {
            strcpy(required[j], tokeni);
            tokeni = strtok(NULL, " ");
        }

        printf("pid -- %s\n", required[0]);
        if (strcmp(required[4], required[7]) == 0)
            printf("Process Status -- %s+\n", required[2]);
        else
            printf("Process Status -- %s\n", required[2]);
        printf("memory -- %s{Virtual Memory}\n", required[8]);
        char path[1000];
        int ret = readlink(exe, path, 1000);
        if (ret != -1)
            printf("Executable Path -- ~/%s\n", required[1]);
        else
            printf("no executable path\n");

        fclose(f);
    }
}