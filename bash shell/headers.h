#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

char previouspath[1000];
char history[20][200];
char initpath[1000];

struct stat *sample;

void prompt();
void pwd();
void cd(char *a);
void echo(char *a);
void ls(char *a);
void repeat(char *a);
void sleepi(char *a);
void fg(char *a);
void bg(char *a);
void pinfo(char *a);
char *filepermission(int size);
void makehistory(char *a);
void historyi(char *a);
void uparrow();
void sendhistorytofile();
void sendfiletohistory();