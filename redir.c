#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
     if(argc == 3){
        fprintf(stderr, "Usage: %s <outputFile> command [<arg1> <arg2> ...]\n", argv[0]);
     }
     int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
     if (fd == -1) {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        return 1;
     }

     char** newargv = (char**)malloc(sizeof(char*) *  (1 + argc - 2));

     for (int ix = 2; ix < argc; ix++){
        newargv[ix-2] = (char*)argv[ix];
     }

     int child_pid = fork();
     if (child_pid == 0){
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execve(newargv[0], newargv, NULL);
     }

     wait(NULL);
     printf("%s pid is %d. forked %d. Parent Exiting\n", argv[0], getpid(), child_pid);

     return 0;
}