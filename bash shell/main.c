#include "headers.h"

int main()
{
    sendfiletohistory();
    getcwd(initpath, 1000);
    while (1)
    {
        prompt();
        char a[1000];

        fgets(a, 1000, stdin);
        a[strlen(a) - 1] = '\0';

        char b[1000];
        char c[1000];
        strcpy(b, a);
        strcpy(c, b);

        makehistory(a);
        sendhistorytofile();
        char stringcolon[100][100];
        char *tokeni = strtok(c, ";");
        int size = 0;
        while (tokeni != NULL)
        {
            strcpy(stringcolon[size], tokeni);
            tokeni = strtok(NULL, ";");
            size++;
        }

        for (int i = 0; i < size; i++)
        {
            char sample[100];
            char string[100];
            strcpy(sample, stringcolon[i]);
            strcpy(string, sample);

            char *token = strtok(sample, " ");

            if (strcmp(token, "quit") == 0)
            {
                exit(0);
            }

            if (string[strlen(string) - 1] == '&' && string[strlen(string) - 2] == ' ')
                bg(string);

            else if (strcmp(token, "cd") == 0)
                cd(string);

            else if (strcmp(token, "echo") == 0)
            {
                echo(string);
            }

            else if (strcmp(token, "pwd") == 0)
                pwd();

            else if (strcmp(token, "ls") == 0)
            {
                ls(string);
            }

            else if (strcmp(token, "sleep") == 0)
            {
                sleepi(string);
            }

            else if (strcmp(token, "repeat") == 0)
                repeat(string);

            else if (strcmp(token, "pinfo") == 0)
                pinfo(string);

            else if (strcmp(token, "history") == 0)
            {
                historyi(string);
            }

            else
            {
                fg(string);
            }
        }
    }
}