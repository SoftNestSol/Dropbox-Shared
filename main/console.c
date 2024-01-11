#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>	


void build_executable_path(char *dest, const char *executables_dir, const char *cmd)
{

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
    if (path == NULL) {
        perror("getcwd() error");
        exit(1);
    }

    char executables_path[1024];

    strncpy(executables_path, path, sizeof(executables_path));

    char *main_substr = strstr(executables_path, "/main");
    if (main_substr != NULL) {
    
        *main_substr = '\0';
    }

    strncat(executables_path, "/executables", sizeof(executables_path) - strlen(executables_path) - 1);

    executables_path[sizeof(executables_path) - 1] = '\0';

  
    while (1)
    {

        char exec_path[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s >", cwd);

        }
        else
        {
            perror("getcwd() error");
            continue;
        }

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Error reading input\n");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
        {
            continue;
        }

        char *command = strtok(input, " ");

        if (command == NULL)
        {
            continue;
        }

        if (strcmp(command, "cwd") == 0)
        {
            printf("%s\n", path);
        }

        else if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            exit(0);
        }

        else if (strcmp(command, "cd") == 0)
        {

            char *path = strtok(NULL, " ");
            if (path == NULL)
            {
                printf("Usage: cd <path>\n");
            }
            else
            {
                int ret = chdir(path);

                if (ret != 0)
                {
                    perror("chdir failed");
                }
            }
        }

        else if (strcmp(command, "cp") == 0)
        {

            char *type = strtok(NULL, " ");
            char *source = strtok(NULL, " ");
            char *destination = strtok(NULL, " ");

            if (type == NULL || source == NULL || destination == NULL)
            {
                printf("Usage: cp <type> <source> <destination>\n");
                printf("Type: local(your machine), dbx (your dropbox), upload(to dropbox), download(from dropbox)\n");
            }
            else
            {
                if (strcmp(type, "local") == 0)
                {   char *execve_cp = strcat(executables_path, "/copy");


                    char *command_args[] = {"copy", source, destination, NULL};

                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
               
                        printf("\n");
                        printf("%s", execve_cp);
                        execve(execve_cp, command_args, NULL);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                else if (strcmp(type, "upload") == 0)
                {

                    char *command_args[] = {"dbxcli", "put", source, destination, NULL};

                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }

                else if (strcmp(type, "download") == 0)
                {

                    char *command_args[] = {"dbxcli", "get", source, destination, NULL};

                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                else if (strcmp(type,"dbx")==0){
                    char *command_args[] = {"dbxcli", "cp", source, destination, NULL};

                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                else
                {
                    printf("Invalid type.\n");
                }
            }
        }

        else if (strcmp(command, "mv") == 0)
        {
            char* type = strtok(NULL, " ");
            char* source = strtok(NULL, " ");
            char* destination = strtok(NULL, " ");

            if(type == NULL || source == NULL)
            {
                printf("Usage: mv <type> <source> <destination>\n");
                printf("Type: local(your machine),dbx(your dropbox) upload(to dropbox), download(from dropbox)\n");
            }

            else{
                if(strcmp(type,"local")==0){

                    char *command_args[] = {"mv", source, destination, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        char *execve_cp = strcat(executables_path, "/copy");
                        execve(execve_cp, command_args,NULL);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                        pid_t pid = fork(); 

                        char* execve_path = strcpy(exec_path,executables_path);
                        char* execve_rm = strcat(execve_path, "/rem");
                        char *command_args[] = {execve_rm, source, NULL};
                        if (pid < 0)
                        {
                            perror("fork failed");
                            exit(1);
                        }
                        else if (pid == 0)
                        {
                            execve(execve_rm, command_args,NULL);
                            perror("execve failed");
                            exit(1);
                        }
                        else
                        {
                            wait(NULL);
                        }
                  

                    }
                }
                else if(strcmp(type,"upload")==0){

                    char *command_args[] = {"dbxcli", "put", source, destination, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                        pid_t pid = fork(); 

                        char* execve_rm = strcat(executables_path, "/rem");
                        char *command_args[] = {execve_rm, source, NULL};

                        if (pid < 0)
                        {
                            perror("fork failed");
                            exit(1);
                        }
                        else if (pid == 0)
                        {
                            execve(execve_rm, command_args,NULL);
                            perror("execve failed");
                            exit(1);
                        }
                        else
                        {
                            wait(NULL);
                        }
                  
                    }
                }

                else if(strcmp(type,"download")==0){

                    char *command_args[] = {"dbxcli", "get", source, destination, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                        pid_t pid = fork(); 

                        char *command_args[] = {"dbxcli", "rm", source, NULL};
                        if (pid < 0)
                        {
                            perror("fork failed");
                            exit(1);
                        }
                        else if (pid == 0)
                        {
                            execvp("dbxcli", command_args);
                            perror("execve failed");
                            exit(1);
                        }
                        else
                        {
                            wait(NULL);
                        }
                  
                    }
                }
                else if (strcmp(type,"dbx")==0){
                    char *command_args[] = {"dbxcli", "mv", source, destination, NULL};

                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
            }
        }

        else if (strcmp(command, "mkdir") == 0)
        {
            char *type = strtok(NULL, " ");
            char *source = strtok(NULL, " ");

            if(type == NULL || source == NULL ){
                printf("Usage: mkdir <type> <source> \n");
                printf("Type: local(your machine), dbx (dropbox)\n");
            }

            else{
                if(strcmp(type,"local")==0){
                    char *command_args[] = {"mkdir", source, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {

                        char *execve_mkdir = strcat(executables_path, "/mkdir");
                        printf("%s\n",execve_mkdir);

                        execve(execve_mkdir, command_args,NULL);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                else if(strcmp(type,"dbx")==0){

                    char *command_args[] = {"dbxcli", "mkdir", source, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
            }

        }

        else if (strcmp(command, "rm") == 0)
        {
            char *type = strtok(NULL, " ");
            char *source = strtok(NULL, " ");
            
            if(type ==NULL || source == NULL ){
                printf("Usage: rm <type> <source> \n");
                printf("Type: local(your machine), dbx (dropbox)\n");
            }
            else{
                if(strcmp(type,"local")==0){
                    char *command_args[] = {"rem", source, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {

                        char *execve_rm = strcat(executables_path, "/rem");
                        printf("%s\n",execve_rm);

                        execve(execve_rm, command_args,NULL);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }

                else if(strcmp(type,"dbx")==0){

                    char *command_args[] = {"dbxcli", "rm", source, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }
                
            }

        }

        else if (strcmp(command, "cat") == 0)
        {
           

            char *path = strtok(NULL, " ");
            char *command_args[] = {"cat", path, NULL};

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork failed");
                exit(1);
            }
            else if (pid == 0)
            {
                char *execve_cat = strcat(executables_path, "/cat");
                execve(execve_cat, command_args, NULL);
                perror("execve failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }

        else if (strcmp(command, "ls") == 0)
        {

            char* type = strtok(NULL, " ");
            char* path = strtok(NULL, " ");

            if(type == NULL || strcmp(type, "dbx") == 0 && path == NULL)
            {
                printf("Usage: ls <type> <path>, <path> is required for dropbox interaction root is '/'\n");
            }

            else{
                if(strcmp(type,"local")==0){
                    char *command_args[] = {"ls", path, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {

                        char *execve_ls = strcat(executables_path, "/ls");
                        printf("%s\n",execve_ls);

                        execve(execve_ls, command_args,NULL);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                    }
                }

                else if(strcmp(type,"dbx")==0){

                    char *command_args[] = {"dbxcli", "ls", path, NULL};
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        perror("fork failed");
                        exit(1);
                    }
                    else if (pid == 0)
                    {
                        execvp("dbxcli", command_args);
                        perror("execve failed");
                        exit(1);
                    }
                    else
                    {
                        wait(NULL);
                        printf("\n");
                    }
                }
            }

           
        }

        else if (strcmp(command, "pwd") == 0)
        {
            char *command_args[2];
            command_args[0] = "pwd";
            command_args[1] = NULL;
        }

        else if (strcmp(command, "help") == 0)
        {

            printf("cp <source> <destination> - copy file\n");
            printf("cd <path> - change directory\n");
            printf("rm <path> - remove file or directory\n");
            printf("mv <source> <destination> - move file\n");
            printf("mkdir <path> - create directory\n");

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