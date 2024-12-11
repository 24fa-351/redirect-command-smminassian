#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
//void split(char **newargv, char **words[], char delimiter);



// void split(char **newargv, char **words[], char delimiter)
// {
//     int word_count = 0;
//     char **next_char = newargv;
//     char current_word[1000];
//     strcpy(current_word, "");

//     while (**next_char != '\0')
//     {
//         if (**next_char == delimiter)
//         {
//             words[word_count++] = strdup(current_word);
//             strcpy(current_word, "");
//         }
//         ++next_char;
//     }
//     words[word_count++] = strdup(current_word);
//     words[word_count] = NULL;
// }


int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(
            stderr,
            "Usage: %s <inputFile> command <outputFile> [<arg1> <arg2> ...]\n",
            argv[0]);
        exit(1);
    }
    char** newargv = (char**)malloc(sizeof(char*) * (1 + argc - 2));
    //char words[argc];
    //split(newargv, words, " ");
    bool redirect_output_to_a_file = false;
    bool redirect_input_to_a_file = false;

    int input_fd;
    if (strcmp(argv[1], "-") != 0) {
        redirect_input_to_a_file = true;
        input_fd = open(argv[1], O_WRONLY | S_IRUSR | S_IWUSR);
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
        printf("Copying %s to newargv[%d]\n", argv[ix], ix - 2);
        newargv[ix - 2] = (char*)argv[ix];
    }

    int child_pid = fork();
    if (child_pid == 0) {
        if (redirect_input_to_a_file) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (redirect_output_to_a_file) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execve(newargv[0], newargv, NULL);
    }
    wait(NULL);
    printf("%s pid is %d. forked %d. Parent Exiting\n", argv[0], getpid(),
           child_pid);

    free(newargv);
    return 0;
}