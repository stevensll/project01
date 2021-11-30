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
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m" 
#define INPUT_SIZE 256
#define OUTPUT_SIZE 5000
#define NAME "PSHell"

int main(){

    //start of shell
    printf("Welcome to ");
    printf("\033[0;36m");
    printf("%s\n\033[0m", NAME);
    
    //loop for each command line
    int running = 1;
    while (running) {

        //print current directory along with "# "
        pwd(RED);
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

                //all other functions
                else {

                    int process;
                    process = fork();

                    //if child, exec command
                    if (!process) {
                        int err = execvp(cmd, args);
                        if (err == -1) printf("%s\n", strerror(errno));
                    }
                    //if parent, wait for child
                    else {
                        int status;
                        wait(&status);
                    }
                }
                free(args);
            }
            else {
                if (pipe) {
                    //printf("cmd1: %s\ncmd2: %s\n", inputs[0], inputs[1]);
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
                }

                //if redirection
                //if redirection out
                else if (redir_out) {
                    int out = open(inputs[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
                    if(out < 0) printf("%s", strerror(errno));
                    int stdout_copy = dup(STDOUT_FILENO);
                    dup2(out, STDOUT_FILENO);
                    //eval

                    int process;
                    process = fork();
                    //if child
                    if (!process) {
                        int err = execvp(inputs[0], get_cmd_args(inputs[0]));
                        if (err == -1) printf("%s\n", strerror(errno));
                    }
                    else {
                        int status;
                        wait(&status);
                    }
                    dup2(stdout_copy, STDOUT_FILENO);
                    close(out);
                    close(stdout_copy);
                }
                //if redirection in
                else if (redir_in) {
                    int in = open(inputs[1], O_RDONLY);
                    if(in < 0) printf("Error redirecting to in file\n%s\n", strerror(errno));
                    int stdin_copy = dup(STDIN_FILENO);
                    dup2(in, STDIN_FILENO);
                    //eval

                    int process;
                    process = fork();
                    //if child
                    if (!process) {
                        int err = execvp(inputs[0], get_cmd_args(inputs[0]));
                        if (err == -1) printf("Error running cmd\n%s\n", strerror(errno));
                    }
                    else {
                        int status;
                        wait(&status);
                    }

                    dup2(stdin_copy, STDIN_FILENO);
                    close(in);
                    close(stdin_copy);
                }

                free(inputs);

                }

            j++;
            cmd = cmds[j];

        }

        free(cmds);

    }

    printf("Exited shell\n");
    return 0;
}