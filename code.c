#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
     int in_fd;
     int out_fd;
    if(argc == 3){
        char *inp = argv[1];
        char *cmd = argv[2];
        char *out = argv[3];

        

        if(strcmp(inp, "-") != 0){
            in_fd = open(inp, O_RDonly);
        }
    }
}