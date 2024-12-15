#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(
            stderr,
            "Usage: %s command <inputFile> <outputFile> [<arg1> <arg2> ...]\n",
            argv[0]);
        exit(1);
    }
    char** newargv = (char**)malloc(sizeof(char*) * (1 + argc - 2));

    
    bool redirect_output_to_a_file = false;
    bool redirect_input_to_a_file = false;

    int input_fd;
    if (strcmp(argv[2], "-") != 0) {
        redirect_input_to_a_file = true;
        input_fd = open(argv[1], O_RDONLY);
        if (input_fd == -1)
            perror("File failed to open");
    }

    int output_fd;
    if (strcmp(argv[3], "-") != 0) {
        redirect_output_to_a_file = true;
        output_fd =
            open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (output_fd == -1)
            perror("File failed to open");
    }

    for (int ix = 2; ix < argc; ix++) {
        printf("Copying %s to newargv[%d]\n", argv[ix], ix - 1);
        newargv[ix - 1] = (char*)argv[ix];
    }
    newargv[argc - 1] = NULL;

    newargv[0] = argv[1];

    int child_pid = fork();
    if (child_pid == 0) {
        if (redirect_input_to_a_file) {
            if (dup2(input_fd, STDIN_FILENO) == -1) {
                perror("Failed to redirect input");
                close(input_fd);
            }
        }
        if (redirect_output_to_a_file) {
            if (dup2(output_fd, STDOUT_FILENO) == -1) {
                perror("Failed to redirect output");
                close(output_fd);
            }
        }

        int val = execve(newargv[0], newargv, NULL);
        if(val == -1){
            perror("Execve failed");
        }
    }
    wait(NULL);
    printf("%s pid is %d. forked %d. Parent Exiting\n", argv[0], getpid(),
           child_pid);

    free(newargv);
    return 0;
}