#include "shell.h"

char ** get_cmd_line(char * line) {
    char *pos;
    if ((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';
    char ** cmds = calloc(sizeof(line)/sizeof(char), sizeof(char *));
    char * curr = line;
    int i = 0;
    while (curr) {
        cmds[i] = strsep(&curr, ";");
        // since we separate each command by ";", we need to remove any white spaces that come after ";"
        // e.g. in "ls -a; echo hi" we want to make sure the cmd is "echo hi", not " echo hi"
        char * temp = cmds[i];
        if(cmds[i][0] == ' '){
            strsep(&(temp), " ");
            cmds[i] = temp;
        }
        i++;
    }
    return cmds;
}

char ** get_cmd_args(char * cmd){
    char ** args = calloc(sizeof(cmd)/sizeof(char), sizeof(char *));
    char * curr = cmd;
    int i = 0;
    while (curr){
        // the first arg will be the cmd
        args[i] = strsep(&curr, " ");
        i++;
    }
    args[i] = NULL;
    return args;
}


void print_string_arr(char ** arr){
    int i = 0;
    while(arr[i]){
        printf("%s\n", arr[i]);
        i++;
    }
    printf("\n");
}

char ** get_cmd_from_pipe(char * line) {
    char ** values = calloc(2, sizeof(char *));
    char * curr = line;
    int i = 0;
    while (curr) {
        values[i] = strsep(&curr, "|");
        i++;
    }
    return values;
}