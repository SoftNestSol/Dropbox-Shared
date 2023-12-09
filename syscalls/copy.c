#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv) {


    const char *source_path = argv[1];
    const char *destination_path = argv[2];

    int source_fd = open(source_path, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    struct stat sb;
    if (stat(source_path, &sb) == -1) {
        perror("Error getting file stats");
        close(source_fd);
        return 1;
    }

    if (sb.st_size == 0) {
        perror("Source file is empty, nothing to copy.\n");
        close(source_fd);
        return 0;
    }

    char *buffer = malloc(sb.st_size);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory\n");
        close(source_fd);
        return 1;
    }

    ssize_t bytes_read = read(source_fd, buffer, sb.st_size);
    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(source_fd);
        free(buffer);
        return 1;
    }
    close(source_fd);

    int target_fd = open(destination_path, O_WRONLY | O_CREAT | O_TRUNC, sb.st_mode);
    if (target_fd == -1) {
        perror("Error opening destination file");
        free(buffer);
        return 1;
    }

    ssize_t bytes_written = write(target_fd, buffer, bytes_read);
    if (bytes_written == -1) {
        perror("Error writing to destination file");
        close(target_fd);
        free(buffer);
        return 1;
    }
    close(target_fd);
    free(buffer);

    return 0;
}
