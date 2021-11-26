#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>
#include "shell.h"
#define INPUT_SIZE 256


int main(){
    //start of shell
    printf("Welcome to Shell!\n");
    int running = 1;
    //loop for each command line
    while (running) {
        printf("# ");
        char input[INPUT_SIZE];
        fgets(input, sizeof(input), stdin);
        char ** cmds = get_cmd_line(input);
        // print_string_arr(args);
        int j = 0;
        //run for every command separated by ;
        while (cmds[j]) {
            printf("This is cmd[%d]: %s\n", j, cmds[j]);
            char ** args = get_cmd_args(cmds[j]);
            if (!strcmp(args[0], "exit")) {
                printf("Exited shell\n");
                return 0;
            }
            else if (!strcmp(args[0], "cd")) {
                chdir(args[1]);
            }
            else {
                int process;
                process = fork();
                //if child
                if (!process) {
                    execvp(cmds[j], args);
                }
                else {
                    int status;
                    wait(&status);
                }
            }
            j++;
        }
        //run parse args
        //if cd or exit
        //fork
        //run exec
    }
    printf("Exited shell\n");
    return 0;
}