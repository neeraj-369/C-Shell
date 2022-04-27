#include "headers.h"

char *filepermission(int size)
{
    char *k;
    k = malloc(10);
    int a, b, c;
    a = size % 8;
    b = (size / 8) % 8;
    c = ((size / 8) / 8) % 8;
    int j = 0;
    k[0] = '-';

    for (int m = 0; m < 3; m++)
    {
        int t;
        if (m == 0)
            t = c;
        if (m == 1)
            t = b;
        if (m == 2)
            t = a;
        j++;

        int x, y, z;
        z = t % 2;
        y = (t / 2) % 2;
        x = ((t / 2) / 2) % 2;

        if (x == 1)
        {
            k[j] = 'r';
        }
        else
        {
            k[j] = '-';
        }
        j++;
        if (y == 1)
        {
            k[j] = 'w';
        }
        else
        {
            k[j] = '-';
        }
        j++;
        if (z == 1)
        {
            k[j] = 'x';
        }
        else
        {
            k[j] = '-';
        }
    }
    k[10] = '\0';
    return k;
}

void ls(char *a)
{
    char c[1000];
    int i;
    for (i = 0; i < strlen(a); i++)
    {
        c[i] = a[i];
    }
    c[i] = '\0';

    char *token = strtok(c, " ");
    token = strtok(NULL, " ");

    int flagl = 0;
    int flaga = 0;
    int flagdot = 0;
    int flagddot = 0;
    int flagcdash = 0;
    int stringsize = 0;
    char string[30][50];
    char mainstring[200];
    strcpy(mainstring, a);
    char *tokenstring = strtok(mainstring, " ");
    tokenstring = strtok(NULL, " ");
    while (tokenstring != NULL)
    {
        if (strcmp(tokenstring, "-l") == 0)
            flagl = 1;
        else if (strcmp(tokenstring, "-a") == 0)
            flaga = 1;
        else if (strcmp(tokenstring, "-la") == 0 || strcmp(tokenstring, "-al") == 0)
        {
            flaga = 1;
            flagl = 1;
        }
        else if (strcmp(tokenstring, ".") == 0)
        {
            flagdot = 1;
        }
        else if (strcmp(tokenstring, "..") == 0)
        {
            flagddot = 1;
        }
        else if (strcmp(tokenstring, "~") == 0)
        {
            flagcdash = 1;
        }
        else
        {
            strcpy(string[stringsize], tokenstring);

            stringsize++;
        }
        tokenstring = strtok(NULL, " ");
    }

    DIR *d;
    struct dirent *dir;
    if ((stringsize == 0 || (stringsize == 0 && flagdot == 1)) && flagddot == 0 && flagl == 0 && flaga == 0 && flagcdash == 0)
    {
        d = opendir(".");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                    printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
    else if (stringsize == 0 && flagddot == 1 && flagdot == 0 && flagl == 0 && flaga == 0 && flagcdash == 0)
    {
        d = opendir("..");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".DS_Store") && strcmp(dir->d_name, ".localized") != 0)
                    printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
    else if ((flaga == 1 && flagl == 0 && stringsize == 0) && (flagddot == 1 || flagdot == 1))
    {
        if (flagdot == 1)
        {
            printf(".:\n");
            d = opendir(".");
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }

        if (flagddot == 1)
        {
            printf("..:\n");
            d = opendir("..");
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }
    }
    else if ((flagdot == 1 || flagddot == 1))
    {
        if (flagl == 0 && flaga == 0)
        {
            if (flagdot == 1)
            {
                printf(".:\n");
                d = opendir(".");
                if (d)
                {
                    while ((dir = readdir(d)) != NULL)
                    {
                        if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                            printf("%s\n", dir->d_name);
                    }
                    closedir(d);
                }
                printf("\n");
            }

            if (flagddot == 1)
            {
                printf("..:\n");
                d = opendir("..");
                if (d)
                {
                    while ((dir = readdir(d)) != NULL)
                    {
                        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".DS_Store") && strcmp(dir->d_name, ".localized") != 0)
                            printf("%s\n", dir->d_name);
                    }
                    closedir(d);
                    printf("\n");
                }
            }

            for (int i = 0; i < stringsize; i++)
            {

                d = opendir(string[i]);
                if (d)
                {
                    printf("%s:\n", string[i]);
                    while ((dir = readdir(d)) != NULL)
                    {
                        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".DS_Store") && strcmp(dir->d_name, ".localized") != 0)
                            printf("%s\n", dir->d_name);
                    }
                    closedir(d);
                    printf("\n");
                }
                else
                {
                    printf("%s\n", string[i]);
                }
            }
        }
        else if (flagddot == 1 && flagl == 1)
        {
            d = opendir("..");
            DIR *folderi;
            struct dirent *datai;
            folderi = opendir("..");
            long long int sum = 0;
            while ((datai = readdir(folderi)) != NULL)
            {
                struct stat filedatai;
                if (strcmp(datai->d_name, ".") != 0 && strcmp(datai->d_name, "..") != 0 && strcmp(datai->d_name, ".DS_Store") != 0 && strcmp(datai->d_name, ".swo") != 0 && strcmp(datai->d_name, ".swp") != 0)
                {
                    if (stat(datai->d_name, &filedatai) == 0)
                    {
                        sum += filedatai.st_blocks;
                    }
                }
            }
            closedir(folderi);
            printf("total %lld\n", sum);
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                {
                    struct stat filedata;
                    struct tm *foo;
                    if (stat(dir->d_name, &filedata) == 0)
                    {
                        char *filepermissions;

                        filepermissions = filepermission(filedata.st_mode);
                        if (filedata.st_mode / 1000 == 16)
                            filepermissions[0] = 'd';
                        printf("%s ", filepermissions);

                        printf("%2ld ", filedata.st_nlink);
                        struct passwd *pw = getpwuid(filedata.st_uid);
                        struct group *gr = getgrgid(filedata.st_gid);
                        printf("%s  %s  ", pw->pw_name, gr->gr_name);
                        printf("%6ld ", filedata.st_size);
                        char *token;
                        token = strtok(ctime(&filedata.st_mtime), " ");
                        char a[5];
                        char b[5];
                        char c[10];
                        token = strtok(NULL, " ");
                        for (int i = 0; i < 3; i++)
                        {
                            if (i == 0)
                                strcpy(a, token);
                            if (i == 1)
                                strcpy(b, token);
                            if (i == 2)
                                strcpy(c, token);
                            token = strtok(NULL, " ");
                        }
                        c[5] = '\0';
                        printf("%2s %s %s ", b, a, c);
                        printf("%s\n", dir->d_name);
                    }
                }
            }
            closedir(d);
        }
        else if (flagdot == 1 && flagl == 1)
        {
            d = opendir(".");
            struct dirent *datai;
            DIR *folderi;
            folderi = opendir(".");
            long long int sum = 0;
            if (flaga == 0)
            {
                while ((datai = readdir(folderi)) != NULL)
                {
                    struct stat filedatai;
                    if (strcmp(datai->d_name, ".") != 0 && strcmp(datai->d_name, "..") != 0 && strcmp(datai->d_name, ".DS_Store") != 0 && strcmp(datai->d_name, ".swo") != 0 && strcmp(datai->d_name, ".swp") != 0)
                    {
                        if (stat(datai->d_name, &filedatai) == 0)
                        {
                            sum += filedatai.st_blocks;
                        }
                    }
                }

                closedir(folderi);
                printf("total %lld\n", sum);

                while ((dir = readdir(d)) != NULL)
                {
                    if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                    {
                        struct stat filedata;
                        struct tm *foo;
                        if (stat(dir->d_name, &filedata) == 0)
                        {
                            char *filepermissions;

                            filepermissions = filepermission(filedata.st_mode);
                            if (filedata.st_mode / 1000 == 16)
                                filepermissions[0] = 'd';
                            printf("%s ", filepermissions);

                            printf("%2ld ", filedata.st_nlink);
                            struct passwd *pw = getpwuid(filedata.st_uid);
                            struct group *gr = getgrgid(filedata.st_gid);
                            printf("%s  %s  ", pw->pw_name, gr->gr_name);
                            printf("%6ld ", filedata.st_size);
                            char *token;
                            token = strtok(ctime(&filedata.st_mtime), " ");
                            char a[5];
                            char b[5];
                            char c[10];
                            token = strtok(NULL, " ");
                            for (int i = 0; i < 3; i++)
                            {
                                if (i == 0)
                                    strcpy(a, token);
                                if (i == 1)
                                    strcpy(b, token);
                                if (i == 2)
                                    strcpy(c, token);
                                token = strtok(NULL, " ");
                            }
                            c[5] = '\0';
                            printf("%2s %s %s ", b, a, c);
                            printf("%s\n", dir->d_name);
                        }
                    }
                }
            }
            if (flaga == 1)
            {
                while ((datai = readdir(folderi)) != NULL)
                {
                    struct stat filedatai;
                    if (stat(datai->d_name, &filedatai) == 0)
                    {
                        sum += filedatai.st_blocks;
                    }
                }

                closedir(folderi);
                printf("total %lld\n", sum);

                while ((dir = readdir(d)) != NULL)
                {
                    struct stat filedata;
                    struct tm *foo;
                    if (stat(dir->d_name, &filedata) == 0)
                    {
                        char *filepermissions;

                        filepermissions = filepermission(filedata.st_mode);
                        if (filedata.st_mode / 1000 == 16)
                            filepermissions[0] = 'd';
                        printf("%s ", filepermissions);

                        printf("%2ld ", filedata.st_nlink);
                        struct passwd *pw = getpwuid(filedata.st_uid);
                        struct group *gr = getgrgid(filedata.st_gid);
                        printf("%s  %s  ", pw->pw_name, gr->gr_name);
                        printf("%6ld ", filedata.st_size);
                        char *token;
                        token = strtok(ctime(&filedata.st_mtime), " ");
                        char a[5];
                        char b[5];
                        char c[10];
                        token = strtok(NULL, " ");
                        for (int i = 0; i < 3; i++)
                        {
                            if (i == 0)
                                strcpy(a, token);
                            if (i == 1)
                                strcpy(b, token);
                            if (i == 2)
                                strcpy(c, token);
                            token = strtok(NULL, " ");
                        }
                        c[5] = '\0';
                        printf("%2s %s %s ", b, a, c);
                        printf("%s\n", dir->d_name);
                    }
                }
            }
            closedir(d);
        }
    }

    else if (flaga == 0 && flagl == 1 && stringsize == 0)
    {
        d = opendir(".");
        struct dirent *datai;
        DIR *folderi;
        folderi = opendir(".");
        long long int sum = 0;
        while ((datai = readdir(folderi)) != NULL)
        {
            struct stat filedatai;
            if (strcmp(datai->d_name, ".") != 0 && strcmp(datai->d_name, "..") != 0 && strcmp(datai->d_name, ".DS_Store") != 0 && strcmp(datai->d_name, ".swo") != 0 && strcmp(datai->d_name, ".swp") != 0)
            {
                if (stat(datai->d_name, &filedatai) == 0)
                {
                    sum += filedatai.st_blocks;
                }
            }
        }
        closedir(folderi);
        printf("total %lld\n", sum);
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
            {
                struct stat filedata;
                struct tm *foo;
                if (stat(dir->d_name, &filedata) == 0)
                {
                    char *filepermissions;

                    filepermissions = filepermission(filedata.st_mode);
                    if (filedata.st_mode / 1000 == 16)
                        filepermissions[0] = 'd';
                    printf("%s ", filepermissions);

                    printf("%2ld ", filedata.st_nlink);
                    struct passwd *pw = getpwuid(filedata.st_uid);
                    struct group *gr = getgrgid(filedata.st_gid);
                    printf("%s  %s  ", pw->pw_name, gr->gr_name);
                    printf("%6ld ", filedata.st_size);
                    char *token;
                    token = strtok(ctime(&filedata.st_mtime), " ");
                    char a[5];
                    char b[5];
                    char c[10];
                    token = strtok(NULL, " ");
                    for (int i = 0; i < 3; i++)
                    {
                        if (i == 0)
                            strcpy(a, token);
                        if (i == 1)
                            strcpy(b, token);
                        if (i == 2)
                            strcpy(c, token);
                        token = strtok(NULL, " ");
                    }
                    c[5] = '\0';
                    printf("%2s %s %s ", b, a, c);
                    printf("%s\n", dir->d_name);
                }
            }
        }
        closedir(d);
    }
    else if (flagl == 0 && flaga == 1 && stringsize == 0)
    {
        d = opendir(".");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
    else if (flaga == 1 && flagl == 1 && stringsize == 0)
    {
        struct dirent *datai;
        DIR *folderi;
        d = opendir(".");
        folderi = opendir(".");
        long long int sum = 0;
        while ((datai = readdir(folderi)) != NULL)
        {
            struct stat filedatai;

            if (stat(datai->d_name, &filedatai) == 0)
            {
                sum += filedatai.st_blocks;
            }
        }
        closedir(folderi);
        printf("total %lld\n", sum);
        while ((dir = readdir(d)) != NULL)
        {
            struct stat filedata;
            struct tm *foo;
            if (stat(dir->d_name, &filedata) == 0)
            {
                char *filepermissions;

                filepermissions = filepermission(filedata.st_mode);
                if (filedata.st_mode / 1000 == 16)
                    filepermissions[0] = 'd';
                printf("%s ", filepermissions);

                printf("%2ld ", filedata.st_nlink);
                struct passwd *pw = getpwuid(filedata.st_uid);
                struct group *gr = getgrgid(filedata.st_gid);
                printf("%s  %s  ", pw->pw_name, gr->gr_name);
                printf("%6ld ", filedata.st_size);
                char *token;
                token = strtok(ctime(&filedata.st_mtime), " ");
                char a[5];
                char b[5];
                char c[10];
                token = strtok(NULL, " ");
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                        strcpy(a, token);
                    if (i == 1)
                        strcpy(b, token);
                    if (i == 2)
                        strcpy(c, token);
                    token = strtok(NULL, " ");
                }
                c[5] = '\0';
                printf("%2s %s %s ", b, a, c);
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
    else if (strcmp(token, "~") == 0)
    {
        d = opendir(getenv("HOME"));
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                    printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
    else if (stringsize != 0)
    {
        for (int it = 0; it < stringsize; it++)
        {
            if (open(string[it], O_RDONLY) != -1)
            {
                d = opendir(string[it]);
                if (d)
                {
                    if (flagl == 1 && flaga == 1)
                    {
                        struct dirent *datai;
                        DIR *folderi;
                        folderi = opendir(string[it]);
                        long long int sum = 0;
                        while ((datai = readdir(folderi)) != NULL)
                        {
                            struct stat filedatai;
                            if (stat(datai->d_name, &filedatai) == 0)
                            {
                                sum += filedatai.st_blocks;
                            }
                        }
                        closedir(folderi);
                        printf("total %lld\n", sum);
                    }

                    if (flagl == 1 && flaga == 0)
                    {
                        struct dirent *datai;
                        DIR *folderi;
                        folderi = opendir(string[it]);
                        long long int sum = 0;
                        while ((datai = readdir(folderi)) != NULL)
                        {
                            struct stat filedatai;
                            if (strcmp(datai->d_name, ".") != 0 && strcmp(datai->d_name, "..") != 0 && strcmp(datai->d_name, ".DS_Store") != 0 && strcmp(datai->d_name, ".swo") != 0 && strcmp(datai->d_name, ".swp") != 0)
                            {
                                if (stat(datai->d_name, &filedatai) == 0)
                                {
                                    sum += filedatai.st_blocks;
                                }
                            }
                        }
                        closedir(folderi);
                        printf("total %lld\n", sum);
                    }
                    while ((dir = readdir(d)) != NULL)
                    {
                        if (flaga == 1)
                        {
                            if (flagl == 0)
                                printf("%s  ", dir->d_name);
                            if (flagl == 1)
                            {
                                struct stat filedata;
                                struct tm *foo;

                                if (stat(dir->d_name, &filedata) == 0)
                                {
                                    char *filepermissions;

                                    filepermissions = filepermission(filedata.st_mode);
                                    if (filedata.st_mode / 1000 == 16)
                                        filepermissions[0] = 'd';
                                    printf("%s ", filepermissions);

                                    printf("%2ld ", filedata.st_nlink);
                                    struct passwd *pw = getpwuid(filedata.st_uid);
                                    struct group *gr = getgrgid(filedata.st_gid);
                                    printf("%s  %s  ", pw->pw_name, gr->gr_name);
                                    printf("%6ld ", filedata.st_size);
                                    char *token;
                                    token = strtok(ctime(&filedata.st_mtime), " ");
                                    char a[5];
                                    char b[5];
                                    char c[10];
                                    token = strtok(NULL, " ");
                                    for (int i = 0; i < 3; i++)
                                    {
                                        if (i == 0)
                                            strcpy(a, token);
                                        if (i == 1)
                                            strcpy(b, token);
                                        if (i == 2)
                                            strcpy(c, token);
                                        token = strtok(NULL, " ");
                                    }
                                    c[5] = '\0';
                                    printf("%2s %s %s ", b, a, c);
                                    printf("%s\n", dir->d_name);
                                }
                            }
                        }
                        else
                        {
                            if (dir->d_name[0] != '.' && dir->d_name[strlen(dir->d_name) - 1] != '~')
                            {
                                if (flagl == 0)
                                    printf("%s  ", dir->d_name);
                                if (flagl == 1)
                                {
                                    struct stat filedata;
                                    struct tm *foo;

                                    if (stat(dir->d_name, &filedata) == 0)
                                    {
                                        char *filepermissions;

                                        filepermissions = filepermission(filedata.st_mode);
                                        if (filedata.st_mode / 1000 == 16)
                                            filepermissions[0] = 'd';
                                        printf("%s ", filepermissions);
                                        printf("%2ld ", filedata.st_nlink);
                                        struct passwd *pw = getpwuid(filedata.st_uid);
                                        struct group *gr = getgrgid(filedata.st_gid);
                                        printf("%s  %s  ", pw->pw_name, gr->gr_name);
                                        printf("%6ld ", filedata.st_size);
                                        char *token;
                                        token = strtok(ctime(&filedata.st_mtime), " ");
                                        char a[5];
                                        char b[5];
                                        char c[10];
                                        token = strtok(NULL, " ");
                                        for (int i = 0; i < 3; i++)
                                        {
                                            if (i == 0)
                                                strcpy(a, token);
                                            if (i == 1)
                                                strcpy(b, token);
                                            if (i == 2)
                                                strcpy(c, token);
                                            token = strtok(NULL, " ");
                                        }
                                        c[5] = '\0';
                                        printf("%2s %s %s ", b, a, c);
                                        printf("%s\n", dir->d_name);
                                    }
                                }
                            }
                        }
                    }
                    if (flagl == 0)
                        printf("\n");
                    closedir(d);
                }
                else
                {
                    if (flagl == 0)
                        printf("%s\n", string[it]);
                    if (flagl == 1)
                    {
                        struct stat filedata;
                        struct tm *foo;
                        if (stat(string[it], &filedata) == 0)
                        {
                            char *filepermissions;

                            filepermissions = filepermission(filedata.st_mode);
                            if (filedata.st_mode / 1000 == 16)
                                filepermissions[0] = 'd';
                            printf("%s ", filepermissions);
                            printf("%2ld ", filedata.st_nlink);
                            struct passwd *pw = getpwuid(filedata.st_uid);
                            struct group *gr = getgrgid(filedata.st_gid);
                            printf("%s  %s  ", pw->pw_name, gr->gr_name);
                            printf("%6ld ", filedata.st_size);
                            char *token;
                            token = strtok(ctime(&filedata.st_mtime), " ");
                            char a[5];
                            char b[5];
                            char c[10];
                            token = strtok(NULL, " ");
                            for (int i = 0; i < 3; i++)
                            {
                                if (i == 0)
                                    strcpy(a, token);
                                if (i == 1)
                                    strcpy(b, token);
                                if (i == 2)
                                    strcpy(c, token);
                                token = strtok(NULL, " ");
                            }
                            c[5] = '\0';
                            printf("%2s %s %s ", b, a, c);
                            printf("%s\n", string[it]);
                        }
                    }
                }
            }
        }
    }
}