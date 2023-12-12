#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(char argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <source> <path>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        char *command_args[] = {argv[1], argv[2], NULL};
        execve("../executables/copy", command_args, NULL);
        perror("execve failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        char *command_args[] = {argv[1], NULL};
        execve("../executables/rem", command_args, NULL);
        perror("execve failed");
        exit(1);
    }

    return 0;
}