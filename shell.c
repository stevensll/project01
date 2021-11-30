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

        // since we separate each command by ";", we need to remove any white spaces that come before and after ";"
        // e.g. in "ls -a ; echo hi" we want to make sure the cmd is "echo hi", not " echo hi"
        char * temp = cmds[i];
        if(cmds[i][0] == ' '){
            strsep(&(temp), " ");
            cmds[i] = temp;
        }
        temp = cmds[i];
        if (cmds[i][strlen(cmds[i])-1] == ' ') {
            temp[strlen(cmds[i])-1] = '\0';
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
        printf("arr[%d] = %s\n", i, arr[i]);
        i++;
    }
    printf("\n");
}

char ** get_cmd_from_operator(char * line, char * operator) {
    char ** values = calloc(2, sizeof(char *));
    char * curr = line;
    int i = 0;
    while (curr) {
        values[i] = strsep(&curr, operator);
        char * temp = values[i];
        if(values[i][0] == ' '){
            strsep(&(temp), " ");
            values[i] = temp;
        }
        temp = values[i];
        if (values[i][strlen(values[i])-1] == ' ') {
            temp[strlen(values[i])-1] = '\0';
        }

        i++;
    }
    return values;
}