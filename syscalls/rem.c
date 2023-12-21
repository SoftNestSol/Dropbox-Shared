#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    struct stat path_stat;
    char *path = argv[1];
    if (stat(path, &path_stat) != 0) {
        perror("Failed to get file status");
        return -1;
    }

    if (S_ISREG(path_stat.st_mode)) { 
        if (unlink(path) != 0) {
            perror("Failed to remove file");
            return -1;
        }
    } else if (S_ISDIR(path_stat.st_mode)) { 
        if (rmdir(path) != 0) {
            perror("Failed to remove directory");
            return -1;
        }
    } else {
        fprintf(stderr, "Unsupported file type\n");
        return -1;
    }

    return 0;
}