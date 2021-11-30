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
#define NAME "PSHell"
#define INPUT_SIZE 500
#define NAME "PSHell"

int main(){

    //start of shell
    printf("Welcome to ");
    printf("\033[0;36m");
    printf("%s\n\033[0m", NAME);
    char color = 'r';
    
    //loop for each command line
    int running = 1;
    while (running) {

        //print current directory in color along with "# "
        pwd(color);
        printf("# ");

        //get line of input, parses it for ';' to get each command segment
        char input[INPUT_SIZE];
        fgets(input, sizeof(input), stdin);
        char ** cmds = get_cmd_line(input);

        //run for every command separated by ;
        int j = 0;
        char * cmd = cmds[j];
        while (cmd) {
            
            char ** inputs;

            //check for pipe
            int pipe = 0;
            if (strstr(cmd, " | ") || strchr(cmd, '|')) {
                pipe = 1;
                char * operator = "|";
                inputs = get_cmd_from_operator(cmd, operator);
            }

            //check for redirection out
            int redir_out = 0;
            if (strstr(cmd, " > ") || strchr(cmd, '>')) {
                redir_out = 1;
                char * operator = ">";
                inputs = get_cmd_from_operator(cmd, operator);
            }

            //check for redirection in
            int redir_in = 0;
            if (strstr(cmd, " < ") || strchr(cmd, '<')) {
                redir_in = 1;
                char * operator = "<";
                inputs = get_cmd_from_operator(cmd, operator);
            }

            //if general case (no '|', '>', or '<')
            if (!(pipe | redir_in | redir_out)) {

                //get arguments from command (parses by " ")
                char ** args;
                args = get_cmd_args(cmd);

                //if exit
                if (!strcmp(args[0], "exit")) {
                    printf("Exited shell\n");
                    return 0;
                }

                //if cd
                else if (!strcmp(args[0], "cd")) {
                    chdir(args[1]);
                }            

                else if (!strcmp(args[0], "color")) {
                    if (!strcmp(args[1], "blue")) {
                        color = 'b';
                    }
                    else if (!strcmp(args[1], "green")) {
                        color = 'g';
                    }
                    else if (!strcmp(args[1], "red")) {
                        color = 'r';
                    }
                    else {
                        printf("Invalid Color. Try \"blue\", \"green\", or \"red\". \n");
                    }
                }            

                //all other functions
                else {
                    exec_cmd(cmd, args);
                }

                free(args);
            }

            //if special case ('|', '>', or '<')
            else {

                //if pipe
                if (pipe) {
                    exec_pipe(inputs);
                }

                //if redirection out
                else if (redir_out) {
                    exec_redir_out(inputs);
                }

                //if redirection in
                else if (redir_in) {
                    exec_redir_in(inputs);
                }

                free(inputs);
            }

            //increment j and move on to next command
            j++;
            cmd = cmds[j];

        }

        free(cmds);

    }

    printf("Exited shell\n");
    return 0;
}