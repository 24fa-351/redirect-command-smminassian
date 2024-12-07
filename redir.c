#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
     if(argc < 3){
        fprintf(stderr, "Usage: %s <outputFile> command [<arg1> <arg2> ...]\n", argv[0]);
        exit(1);
     }
     char** newargv = (char**)malloc(sizeof(char*) *  (1 + argc - 2));
      bool redirect_output_to_a_file = false;
      int fd;
     if(strcmp(argv[1], "-") != 0){
      redirect_output_to_a_file = true;
      fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
     }


      for (int ix = 2; ix < argc; ix++){
         printf("Copying %s to newargv[%d]\n", argv[ix], ix-2);
         newargv[ix-2] = (char*)argv[ix];
     }

     int child_pid = fork();
     if (child_pid == 0){
      if(redirect_output_to_a_file){
        dup2(fd, STDOUT_FILENO);
        close(fd);
      }

        execve(newargv[0], newargv, NULL);
     }
      wait(NULL);
     printf("%s pid is %d. forked %d. Parent Exiting\n", argv[0], getpid(), child_pid);
     
    
      
      free(newargv);
      return 0;
}