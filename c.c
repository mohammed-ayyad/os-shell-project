#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0)
    {
        execlp("ls", "ls", NULL);
    }
    else
    {
        wait(0);
    }
}