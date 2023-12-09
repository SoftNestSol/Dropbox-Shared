#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void shell()
{
    printf("Welcome to the shell!\n");
    printf("Type 'exit' to exit the shell.\n");
    printf("Type 'help' to see the list of commands.\n");

    char input[2000];
    int status = 1;
    char* command = malloc(2000);

    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s >", cwd);
        } else {
            perror("getcwd() error");
            continue;
        }

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        char *command = strtok(input, " ");

        if (command == NULL) {
            continue;
        }

        if (strcmp(command, "exit") == 0) {
            status = 0;
        } 
        
        else if (strcmp(command, "cd") == 0) {

            char *path = strtok(NULL, " ");
            if (path == NULL) {
                printf("Usage: cd <path>\n");
            } else {
                if (chdir(path) != 0) {
                    perror("cd failed");
                }
            }
        } 
        
        else if (strcmp(command, "cp") == 0) {
            char *source = strtok(NULL, " ");
            char *destination = strtok(NULL, " ");
            if (source == NULL || destination == NULL) {
                printf("Usage: cp <source> <destination>\n");
            } 
            
        else {
                char *command_args[] = {"cp", source, destination, NULL};
                
                pid_t pid = fork();

                if (pid < 0) {
                    perror("fork failed");
                    exit(1);
                } else if (pid == 0) {
                    execve("../executables/copy", command_args, NULL);
                    perror("execve failed"); 
                    exit(1); 
                } else {
                    wait(NULL);
                }
            }
    }


    else if(strcmp(command, "mv") == 0)
    {
        char* command_args[4];
        command_args[0] = "mv";
        scanf("%s", command_args[1]);
        scanf("%s", command_args[2]);
        command_args[3] = NULL;

    }

    else if(strcmp(command, "mkdir") == 0)
    {
        char* command_args[3];
        command_args[0] = "mkdir";
        scanf("%s", command_args[1]);
        command_args[2] = NULL;

    }

    else if(strcmp(command, "rmdir") == 0)
    {
        char* command_args[3];
        command_args[0] = "rmdir";
        scanf("%s", command_args[1]);
        command_args[2] = NULL;
   
    }

    else if(strcmp(command, "rm") == 0)
    {
        char* command_args[3];
        command_args[0] = "rm";
        scanf("%s", command_args[1]);
        command_args[2] = NULL;

    }

    else if(strcmp(command, "cat") == 0)
    {
        char* command_args[3];
        command_args[0] = "cat";
        scanf("%s", command_args[1]);
        command_args[2] = NULL;

    }

    else if(strcmp(command, "ls") == 0)
    {
        char* command_args[3];
        command_args[0] = "ls";
        scanf("%s", command_args[1]);
        command_args[2] = NULL;

    }

    else if(strcmp(command, "pwd") == 0)
    {
        char* command_args[2];
        command_args[0] = "pwd";
        command_args[1] = NULL;

    }

    else if(strcmp(command, "help") == 0)
    {
        printf("cd <path> - change directory\n");
        printf("cp <source> <destination> - copy file\n");
        printf("mv <source> <destination> - move file\n");
        printf("mkdir <path> - create directory\n");
        printf("rmdir <path> - remove directory\n");
        printf("rm <path> - remove file\n");
        printf("cat <path> - print file contents\n");
        printf("ls <path> - list directory contents\n");
        printf("pwd - print working directory\n");
        printf("clear - clear the screen\n");
        printf("exit - exit the shell\n");
    }

    else if (strcmp(command, "clear") == 0)
    {
        system("clear");
    }

    else
    {
        printf("Command not found.\n");
    }
    
    }

    free(command);

    if(status == 0)
    {
        printf("Exiting shell...\n");
        exit(0);
    }

}

int main()
{

    shell();


    return 0;
}