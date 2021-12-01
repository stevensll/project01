#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#define OUTPUT_SIZE 7500

//SETUP COMMANDS--------------------------------------------------------------------------------------------------

/*
    pwd takes in a character representing a specific color ('r' = RED, 'b' = BLUE, 'g' = GREEN), and prints the 
    current working directory in the given color. It has a void return type.
*/
void pwd(char color);

//----------------------------------------------------------------------------------------------------------------

//PARSE COMMANDS--------------------------------------------------------------------------------------------------

/*
    get_cmd_line takes in a string (char array) and parses through it for ";", returning an array of strings
    that were separated by the ";". Any space before and after the ";" is removed.
*/
char ** get_cmd_line( char * line );

/*
    get_cmd_args takes in a string (char array) and parses through it for " ", returning an array of strings
    that were separated by the " ".
*/
char ** get_cmd_args(char * cmd);

/*
    get_cmd_from_operator takes in two strings (char array), line and operator, and separates line at where the
    operator ('|', '>', or '<') is in the line to return a two-string array (char **). Any space before and after
    the operator is removed.
*/
char ** get_cmd_from_operator(char * line, char * operator);

/*
    print_string_arr takes in a string array and prints it out. It has a void return type. (for testing)
*/
void print_string_arr(char ** arr);

//-----------------------------------------------------------------------------------------------------------------

//EXEC COMMANDS----------------------------------------------------------------------------------------------------

/*
    exec_pipe takes in a two string array (char **), input, that contains the two commands that are to be piped
    together, and executes the pipe operation using popen. It has a void return type.
*/
void exec_pipe(char ** inputs);

/*
    exec_redir_out takes in a two string array (char **), input, that contains two commands, and executes 
    the "<" operation by redirecting the stdin of the first command from the second command. It has a void return type.
*/
void exec_redir_out(char ** inputs);

/*
    exec_redir_in takes in a two string array (char **), input, that contains two commands, and executes 
    the "<" operation by redirecting the stdout of the first command to the second command. It has a void return type.
*/
void exec_redir_in(char ** inputs);

/*
    exec_cmd takes in a string (char array) representing a command and a string array (char **) representing its arguments
    and executes the command by forking execvp to a child process. It has a void return type.
*/
void exec_cmd(char * cmd, char ** args);

//-----------------------------------------------------------------------------------------------------------------