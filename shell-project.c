#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
void exe(char *arg1, char *arg[], int and_word_index)
{
    pid_t pid = fork();
    if (pid == 0)
    {

        execvp(arg1, arg);
    }
    else
    {
        if (and_word_index == -1)
        {
            wait(NULL);
        }
        else
        {
            printf("pid[%d]\n", pid);
        }
    }
}

char *trim(char *str)
{
    while (str[0] == ' ')
        str++;

    while (str[strlen(str) - 1] == ' ')
        str[strlen(str) - 1] = '\0';

    return str;
}

int main(int argc, char *argv[])
{
    char *argx[100] = {0};
    if (argc > 1)
    {
        int x = open(argv[1], O_RDONLY, 0777);
        if (x == -1)
        {
            printf("file dose not exist\n");
            exit(0);
        }
        dup2(x, 0);
    }
    while (1)
    {
        char c_path[1000];
        getcwd(c_path, 1000);

        char command[10000] = {0};

        if (argc > 1)
        {
            //char v[10000] = {0};
            char c = fgetc(stdin);
            if (c == EOF)
            {
                exit(0);
            }
            printf("\n\e[0;31m┌──(%s\e[0;33m㉿\e[1;34mkali\033[0;31m)-[~\e[1;32m%s\033[0;31m]\n└─\e[1;34m$ \e[0m\n", getenv("USER"), c_path);
            fflush(0);

            for (int i = 0; c != '\n' && c != EOF; i++)
            {
                command[i] = c;
                c = fgetc(stdin);
            };
        }
        else
        {
            printf("\n\e[0;31m┌──(%s\e[0;33m㉿\e[1;34mkali\033[0;31m)-[~\e[1;32m%s\033[0;31m]\n└─\e[1;34m$ \e[0m", getenv("USER"), c_path);
            fflush(0);

            fgets(command, sizeof(command), stdin);
            command[strlen(command) - 1] = '\0';
        }

        char command2[1000];
        strcpy(command2, command);
        char *arg[1000] = {0};
        arg[0] = strtok(command2, " ");
        int is_g_sign = -1;
        int is_2g_sign = -1;
        int and_word_index = -1;

        for (int i = 0; arg[i] != NULL; i++)
        {
            arg[i + 1] = strtok(NULL, " ");

            if (strstr(arg[i], ">") != 0)
                is_g_sign = i;
            if (strstr(arg[i], ">>") != 0)
            {
                is_2g_sign = i;
                is_g_sign = -1;
            }
        }

        if (arg[0] == NULL)
        {
            continue;
        }

        for (int i = 0; arg[i] != NULL; i++)
        {
            if (strcmp(arg[i], "&") == 0 && arg[i + 1] == NULL)
            {
                and_word_index = i;
            }
            if (arg[i][strlen(arg[i]) - 1] == '&' && arg[i + 1] == NULL)
            {
                arg[i][strlen(arg[i]) - 1] = '\0';
                and_word_index = i + 1;
            }
        }
        if (and_word_index != -1)
        {
            arg[and_word_index] = 0;
        }

        if (strcmp(arg[0], "pause") == 0)
        {
            char enter = 0;
            printf("press Enter to resume ....");
            while (enter != '\n')
            {
                scanf("%c", &enter);
            }
            continue;
        }

        if (strcmp(arg[0], "quit") == 0)
        {
            exit(0);
        }

        if (strcmp(arg[0], "dir") == 0)
        {
            strcpy(arg[0], "ls");
            strcpy(arg[0], "ls");
            // exe(arg[0], arg, and_word_index);
            // continue;
        }
        if (strcmp(arg[0], "clr") == 0)
        {
            strcpy(arg[0], "clear");
            strcpy(arg[0], "clear");
            // exe(arg[0], arg, and_word_index);
            // continue;
        }
        if (strcmp(arg[0], "environ") == 0)
        {
            strcpy(arg[0], "env");
            strcpy(arg[0], "env");
            // exe(arg[0], arg, and_word_index);
            // continue;
        }
        if (strcmp(arg[0], "help") == 0)
        {
            arg[0] = "more";
            arg[1] = "/home/m/Desktop/shell/shlast/help.txt";
            arg[2] = NULL;
            // exe(arg[0], arg, and_word_index);
            // continue;
        }
        if (strcmp(arg[0], "cd") == 0)
        {
            char old[1000] ;
            getcwd(old, 1000);
            char newpath[1000];
            if (arg[1] == NULL)
            {
                printf("wrong path");
                continue;
            }

            if (arg[1][0] != '/')
            {
                strcpy(old, strcat(old, "/"));
            }
            char p[1000] = {0};
            for (int i = 1; arg[i] != NULL; i++)
            {
                strcpy(p, strcat(strcat(p, " "), arg[i]));
            }
            char *p2 = trim(p);
            strcpy(newpath, strcat(old, p2));
            if (chdir(newpath) != 0)
            {
                printf("\e[1;31mfailed to get current directory\n");
                continue;
            }
            continue;
        }

        char command3[1000];
        strcpy(command3, command);
        char *arg2[2] = {0};
        if (is_g_sign != -1)
        {
            arg2[0] = strtok(command3, ">");
            arg2[1] = strtok(NULL, ">");
            arg2[2] = 0;
            arg2[0] = trim(arg2[0]);
            arg2[1] = trim(arg2[1]);
            char *arg3[100] = {0};
            arg3[0] = strtok(arg2[0], " ");
            for (int i = 0; arg3[i] != NULL; i++)

                arg3[i + 1] = strtok(NULL, " ");

            int fd = open(arg2[1], O_RDWR | O_CREAT, 0777);

            int pid2 = fork();
            if (pid2 == 0)
            {
                dup2(fd, 1);
                execvp(arg2[0], arg3);
            }
            else
            {
                wait(0);
            }
            continue;
        }
        if (is_2g_sign != -1)
        {
            arg2[0] = strtok(command3, ">>");
            arg2[1] = strtok(NULL, ">>");
            arg2[2] = 0;

            arg2[0] = trim(arg2[0]);
            arg2[1] = trim(arg2[1]);
            char *arg3[100] = {0};
            arg3[0] = strtok(arg2[0], " ");
            for (int i = 0; arg3[i] != NULL; i++)

                arg3[i + 1] = strtok(NULL, " ");

            int fd = open(arg2[1], O_APPEND | O_RDWR | O_CREAT, 0777);

            int pid2 = fork();
            if (pid2 == 0)
            {
                dup2(fd, 1);
                execvp(arg2[0], arg3);
            }
            else
            {
                wait(0);
            }
            continue;
        }
        exe(arg[0], arg, and_word_index);
    }
}