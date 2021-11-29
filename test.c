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
#define OUTPUT_SIZE 1000


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
        char * cmd = cmds[j];
        printf("%s\n", cmd);
        //run for every command separated by ;
        while (cmds[j]) {
            //printf("This is cmd[%d]: %s\n", j, cmd);
            char ** args = get_cmd_args(cmd);
            //if exit
            if (!strcmp(args[0], "exit")) {
                printf("Exited shell\n");
                return 0;
            }
            //if cd
            else if (!strcmp(args[0], "cd")) {
                chdir(args[1]);
            }
            // if pipe
            else if (strchr(cmd, '|')) {

                /*earlier code for different method, was going to use popen to get 
                output of first command, then exec using that output*/

                //printf("There is a |\n");
                // char ** inputs = get_cmd_from_pipe(cmd);
                // printf("cmd1: %s\ncmd2: %s\n", inputs[0], inputs[1]);
                // FILE * fp;
                // int status;
                // char output[OUTPUT_SIZE];
                // fp = popen


                FILE *fp = popen(cmd, "r");
                //writes output of pipe to file fp
                char c = fgetc(fp);
                //prints out file
                while (c != EOF) {
                    printf("%c", c);
                    c = fgetc(fp);
                }
                pclose(fp);
            }
            // if regular function
            else {
                int process;
                process = fork();
                //if child
                if (!process) {
                    execvp(cmd, args);
                }
                else {
                    int status;
                    wait(&status);
                }
            }
            j++;
        }
    }
    printf("Exited shell\n");
    return 0;
}