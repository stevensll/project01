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
#define OUTPUT_SIZE 5000
#define NAME "PShell"

int main(){
    //start of shell
    printf("Welcome to ");
    printf("\033[0;36m");
    printf("%s\n\033[0m", NAME);
    int running = 1;
    //loop for each command line
    while (running) {
        printf("# ");
        char input[INPUT_SIZE];
        fgets(input, sizeof(input), stdin);
        char ** cmds = get_cmd_line(input);
        //print_string_arr(cmds);
        int j = 0;
        char * cmd = cmds[j];
        //printf("%s\n", cmd);
        //run for every command separated by ;
        while (cmd) {
            printf("This is cmd[%d]: %s\n", j, cmd);

            int pipe = 0;
            char ** inputs;
            if (strstr(cmd, " | ") || strchr(cmd, '|')) {
                pipe = 1;
                char * operator = "|";
                inputs = get_cmd_from_operator(cmd, operator);
            }
            int redir_to = 0;
            if (strstr(cmd, " > ") || strchr(cmd, '>')) {
                redir_to = 1;
                char * operator = ">";
                inputs = get_cmd_from_operator(cmd, operator);
            }
            int redir_from = 0;
            if (strstr(cmd, " < ") || strchr(cmd, '<')) {
                redir_from = 1;
                char * operator = "|";
                inputs = get_cmd_from_operator(cmd, operator);
            }


            char ** args = get_cmd_args(cmd);
            //print_string_arr(args);
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
            else if (pipe) {
                
                printf("cmd1: %s\ncmd2: %s\n", inputs[0], inputs[1]);
                FILE *output, *input;
                char data[OUTPUT_SIZE];
                output = popen(inputs[0], "r");
                input = popen(inputs[1], "w");
                // while (fgets(data, OUTPUT_SIZE, output)) {
                //     printf("%s", data);
                // }
                while (fgets(data, OUTPUT_SIZE, output)) {
                    fputs(data, input);
                }
                pclose(output);
                pclose(input);

                /*
                bad method
                FILE *fp = popen(cmd, "r");
                //writes output of pipe to file fp
                char c = fgetc(fp);
                //prints out file
                while (c != EOF) {
                    printf("%c", c);
                    c = fgetc(fp);
                }
                pclose(fp);
                */
            }

            //if redirection

            // if  a < b
            // else if () {

            // }

            // if a > b
            // else if () {

            // }

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
            free(args);
            free(inputs);
            j++;
            cmd = cmds[j];
        }
        free(cmds);
    }
    printf("Exited shell\n");
    return 0;
}