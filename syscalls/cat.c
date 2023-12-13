#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

    if (argc < 2) {
        printf("Usage: cat <path>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file\n");
        return 1;
    }

    char c = EOF;

    while((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }

    printf("\n");
    fclose(file);


    return 0;
}