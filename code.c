#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
     if(argc == 4){
        char**newargv = (char**)malloc(sizeof(char*) * argc-1);

        for(int ix = 1; ix < argc; ix++){
            newargv[ix-1] = (char*)argv[ix];
        }
        newargv[argc-1] = NULL;

        printf("arr[2]:  %s\n", argv[2]);
        printf("arr[3]: %s\n", argv[3]);

        //Need to make argv[1] and argv[2] be one output. So this means that i need to split the space in between the argv2 and argv3 and the push that 
        //split to newargv[1]
        free(newargv);
     }
     return 0;
}