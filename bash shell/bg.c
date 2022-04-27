#include "headers.h"

int asfd = 0;
char asfds[100];
void handler(int sig)
{
    pid_t pid;
    pid = wait(NULL);

    char hostname[101];
    gethostname(hostname, 101);

    if (asfd == 1)
    {
        printf("\n%s with pid %d exited normally\n", asfds, pid);

        prompt();
        fflush(stdout);
    }
    asfd = 0;
}

void bg(char *a)
{
    asfd = 1;
    char c[1000];
    int i;
    strcpy(c, a);
    char *token = strtok(c, " ");
    strcpy(asfds, token);

    int pid = fork();
    if (pid > 0)
        signal(SIGCHLD, handler);

    if (pid == 0)
    {
        if (strcmp(token, "sleep") == 0)
        {
            int sum = 0;
            int pow = 1;
            token = strtok(NULL, " ");
            for (int i = strlen(token) - 1; i >= 0; i--)
            {
                int time = token[i] - 48;
                sum += time * pow;
                pow = pow * 10;
            }
            printf("\n%d\n", getpid());
            prompt();
            fflush(stdout);
            sleep(sum);
            exit(1);
        }
        else
        {
            printf("\n%d\n", getpid());
            prompt();
            fflush(stdout);
            char *exec_args[] = {token, NULL};
            if (execvp(token, exec_args) == -1)
            {
                asfd = 0;
                perror("No such bg process");
                exit(0);
            }
            fflush(stdout);
        }
    }
}