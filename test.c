#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#DEFINE INPUT_SIZE 256


int main(){
    
    printf("Welcome to \n");
    running = 1;
    while (running) {
        printf("# ");
        char[INPUT_SIZE] input;
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        char ** args = parse_args(input);
        
        //run parse args
        //if cd or exit
        //run exec
        //fork
    }
    printf("Exited shell\n");
    return 0;
}