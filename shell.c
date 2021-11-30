#include "shell.h"

//SETUP COMMANDS--------------------------------------------------------------------------------------------------

void pwd(char * color){
    printf("%s", color);
    FILE *wd;
    char data[100];
    wd = popen("pwd", "r");
    fgets(data, 100, wd);
    pclose(wd);
    char * copy = data;
    data[strlen(data)-1] = '\0';
    printf("%s", data);
    printf("\033[0m");
}

//----------------------------------------------------------------------------------------------------------------

//PARSE COMMANDS--------------------------------------------------------------------------------------------------

char ** get_cmd_line(char * line) {

    //deletes newline at the end of the input
    char *pos;
    if ((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';

    char ** cmds = calloc(sizeof(line)/sizeof(char), sizeof(char *));
    char * curr = line;

    //parsing by ";"
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

void print_string_arr(char ** arr){
    int i = 0;
    while(arr[i]){
        printf("arr[%d] = %s\n", i, arr[i]);
        i++;
    }
    printf("\n");
}

//-----------------------------------------------------------------------------------------------------------------

//EXEC COMMANDS----------------------------------------------------------------------------------------------------

void exec_pipe(char ** inputs) {
    FILE *output, *input;
    char data[OUTPUT_SIZE];
    output = popen(inputs[0], "r");
    input = popen(inputs[1], "w");
    while (fgets(data, OUTPUT_SIZE, output)) {
        fputs(data, input);
    }
    pclose(output);
    pclose(input);
}

void exec_redir_out(char ** inputs) {
    //create file
    int out = open(inputs[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    //error check
    if (out < 0) printf("%s", strerror(errno));
    //save stdout
    int stdout_copy = dup(STDOUT_FILENO);
    //redirect stdout to file
    dup2(out, STDOUT_FILENO);

    //execute command
    exec_cmd(inputs[0], get_cmd_args(inputs[0]));

    //redirect stdout back to backed up copy
    dup2(stdout_copy, STDOUT_FILENO);

    //close files
    close(out);
    close(stdout_copy);
}

void exec_redir_in(char ** inputs) {

    //create file
    int in = open(inputs[1], O_RDONLY);
    //error check 
    if (in < 0) printf("Error redirecting to in file\n%s\n", strerror(errno));
    //save stdin
    int stdin_copy = dup(STDIN_FILENO);
    //redirect stdin to file
    dup2(in, STDIN_FILENO);
                    
    //evaluate command
    exec_cmd(inputs[0], get_cmd_args(inputs[0]));

    //redirect stdin back to backed up copy
    dup2(stdin_copy, STDIN_FILENO);

    //close files
    close(in);
    close(stdin_copy);

}

void exec_cmd(char * cmd, char ** args) {
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

//-----------------------------------------------------------------------------------------------------------------