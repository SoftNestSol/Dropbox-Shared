#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
    printf("Usage: %s <dir name>\n", argv[0]);
    if (argc != 2)
    {
        printf("Usage: %s <dir name>\n", argv[0]);
        return 1;
    }

    char * command_args = argv[2];
    int ret = mkdir(command_args,0777);
    if (ret != 0)
    {
        perror("mkdir failed");
        return 1;
    }
    return 0;
}