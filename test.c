#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "shell.h"
#define INPUT_SIZE 256


int main(){
    
    printf("Welcome to \n");
    int running = 1;
    while (running) {
        printf("# ");
        char input[INPUT_SIZE];
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        char ** args = parse_args(input);
        print_2d_arr(args);
        if (args[0]) {
            if (!strcmp(args[0], "exit")) {
                running = 0;
                break;
            }
            else if (!strcmp(args[0], "cd")) {
                chdir(args[1]);
            }
            else if (args[1]) {
                printf("%s", args[1]);
                // execvp(args[0], args);
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