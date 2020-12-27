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

char *trim(char *str)
{
    char *end;
    /* skip leading whitespace */
    while (isspace(*str))
    {
        str = str + 1;
    }
    /* remove trailing whitespace */
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
    {
        end = end - 1;
    }
    /* write null character */
    *(end + 1) = '\0';
    return str;
}

int main(int argc, char *argv[])
{
    while (1)
    {   
        char c_path[100];
        getcwd(c_path, 100);
        printf("%s%s%s%s", getenv("USER"), "@Kali:~",c_path, "$ ");
        

        // char command[100];
        // fgets(command, sizeof(command), stdin);
        
        char command[100] = {0};
        int fillindex = 0;
        char ch;

        scanf("%c", &ch);
        while (ch != '\n')
        {
            command[fillindex] = ch;
            fillindex++;
            scanf("%c", &ch);
        }
        char command2[100];
        strcpy(command2, command);

        char *arg[100] = {0};
     
        arg[0] = strtok(command2, " ");
        int is_g_sign = -1;
        int is_2g_sign = -1;

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
        }
        if (strcmp(arg[0], "clr") == 0)
        {
            strcpy(arg[0], "clear");
            strcpy(arg[0], "clear");
        }
        if (strcmp(arg[0], "environ") == 0)
        {
            strcpy(arg[0], "env");
            strcpy(arg[0], "env");
        }
        if (strcmp(arg[0], "help") == 0)
        {
            arg[0] = "more";
            arg[1] = "help.txt";
            arg[2] = NULL;
        }
        if (strcmp(arg[0], "cd") == 0)
        {
            char old[1000];
            getcwd(old, 1000);
            char newpath[1000];
            

                if (arg[1][0] != '/')
                {
                    strcpy(old, strcat(old, "/"));
                }
                strcpy(newpath, strcat(old, arg[1]));
                if (chdir(newpath) != 0)
                {
                    perror("failed to get current directory\n");
                    continue;
                }
                continue;
            
        }
        //printf("\n%d %d %d",is_g_sign, is_2g_sign, is_and_sign);
        char command3[100];
        strcpy(command3, command);
        char *arg2[100];
        if (is_g_sign != -1)
        {
            arg2[0] = strtok(command3, ">");
            for (int i = 0; arg[i] != NULL; i++)
            arg2[i + 1] = strtok(NULL, ">");
            arg2[0] = trim(arg2[0]);
            arg2[1] = trim(arg2[1]);
            char *arg3[100];
            arg3[0] = strtok(arg2[0], " ");
            for (int i = 0; arg3[i] != NULL; i++)

                arg3[i + 1] = strtok(NULL, " ");

            int x = open(arg2[1], O_RDWR | O_CREAT, 0777);

            int m = fork();
            if (m == 0)
            {
                dup2(x, 1);
                execvp(arg[0], arg3);
            }
            else
            {
                wait(0);
            }
            continue;

            //printf("%s \n%s / %s\n", command, arg[0], arg[1]);
        }
        if (is_2g_sign != -1)
        {
            arg2[0] = strtok(command3, ">>");
            for (int i = 0; arg[i] != NULL; i++)
            arg2[i + 1] = strtok(NULL, ">>");
            arg2[0] = trim(arg2[0]) ;
            arg2[1]= trim(arg2[1]);
            char *arg3[100];
            arg3[0] = strtok(arg2[0], " ");
            for (int i = 0; arg3[i] != NULL; i++)
            
                arg3[i + 1] = strtok(NULL, " ");

            int x = open(arg2[1], O_APPEND | O_RDWR | O_CREAT, 0777);

            int m = fork();
            if (m == 0)
            {
                dup2(x, 1);
                execvp(arg[0], arg3);
                }
                else
                {
                    wait(0);
                }
                continue;

                //printf("%s \n%s // %s\n", command, arg[0], arg[1]);
            } 
            int and_word_index = -1;

          
            for (int i= 0; arg[i] != NULL; i++)
            {
                if (strcmp(arg[i], "&") == 0 && arg[i+1] == NULL)
                {
                    and_word_index = i;
                }
            }
            arg[and_word_index]=0;
        
        

            pid_t pid = fork();
        if (pid == 0)
        {

            execvp(arg[0], arg);
        }
        else
        {
           if (and_word_index == -1)
            {
                wait(NULL);
            }
        }
    }
}
