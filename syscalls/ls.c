#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>


int main(int argc, char** argv)
{

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s >", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    DIR *d = opendir(".");

    if (d == NULL) {
        perror("Error opening directory\n");
        return 1;
    }

    struct dirent *dir;

    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
        printf(" %s din ls", cwd);
    }

    closedir(d);



    return 0;
}
