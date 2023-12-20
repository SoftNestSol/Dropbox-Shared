#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void print_differences(const char *str1, const char *str2) {
    int length = strlen(str1) > strlen(str2) ? strlen(str1) : strlen(str2);
    
    printf("Index\tstr1\tstr2\tASCII(str1-str2)\n");
    for (int i = 0; i < length; ++i) {
        char c1 = i < strlen(str1) ? str1[i] : '\0';
        char c2 = i < strlen(str2) ? str2[i] : '\0';
        
        if (c1 != c2) {
            printf("%d\t%c\t%c\t%d\n", i, c1, c2, c1 - c2);
        }
    }
}


void build_executable_path(char* dest, const char* executables_dir, const char* cmd) {
 
    strcpy(dest, executables_dir);
    strcat(dest, "/");
    strcat(dest, cmd);
}


void shell()
{
    printf("\n");
    printf("Welcome to the shell!\n");
    printf("Type 'exit' to exit the shell.\n");
    printf("Type 'help' to see the list of commands.\n");

    char input[2000];

    char cwd[1024];

    char *path = getcwd(cwd, sizeof(cwd));
    char executables_path[1024];
    strncpy(executables_path, path, strlen(path) - 4);
    strcat(executables_path, "executables");



    while (1) {

        char exec_path[1024];


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

        if(strcmp(command, "cwd") == 0)
        {
            printf("%s\n", executables_path);
        }

      else if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            exit(0);
        } 
        
        else if (strcmp(command, "cd") == 0) {

            char *path = strtok(NULL, " ");
            if (path == NULL) {
                printf("Usage: cd <path>\n");
            } else {
               
                int ret = chdir(path);

                if (ret != 0) {
                    perror("chdir failed");
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
                     
                    char* execve_cp = strcat(executables_path, "/copy");
                    execve(execve_cp, command_args, NULL);
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

        char *path = strtok(NULL, " ");
        char* command_args[] = {"cat", path, NULL};

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            char* execve_cat = strcat(executables_path, "/cat");
            execve(execve_cat, command_args, NULL);
            perror("execve failed"); 
            exit(1); 
        } else {
            wait(NULL);
        }
    }

    else if(strcmp(command, "ls") == 0)
    {
        char* command_args[2];
        command_args[0] = "ls";
        command_args[1] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            
            char* execve_ls = strcat(executables_path, "/ls");
            execve(execve_ls , command_args, NULL);
            perror("execve failed"); 
            exit(1); 
        } else {
            wait(NULL);
        }


    }

    else if(strcmp(command, "pwd") == 0)
    {
        char* command_args[2];
        command_args[0] = "pwd";
        command_args[1] = NULL;

    }

    else if(strcmp(command, "help") == 0)
    {
        
        printf("cp <source> <destination> - copy file\n");
        printf("cd <path> - change directory\n");
        printf("rm <path> - remove file\n");
        printf("mv <source> <destination> - move file\n");
        printf("mkdir <path> - create directory\n");
        printf("rmdir <path> - remove directory\n");
        
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



}

int main()
{

    shell();


    return 0;
}