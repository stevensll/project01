#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <shell.h>
#define INPUT_SIZE 256


int main(){
    
    printf("Welcome to \n");
    int running = 1;
    while (running) {
        printf("# ");
        char[INPUT_SIZE] input;
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        char ** args = parse_args(input);
        if (!args[0]) {
            if (!strcmp(args[0], "exit")) {
                running = 0;
                break;
            }
            else if (!strcmp(args[0], "cd")) {
                chdir(args[0]);
            }
        }
        //run parse args
        //if cd or exit
        //run exec
        //fork
    }
    printf("Exited shell\n");
    return 0;
}