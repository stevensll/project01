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
    Prints the current working directory in the given color
*/
void pwd(char * color);

//----------------------------------------------------------------------------------------------------------------

//PARSE COMMANDS--------------------------------------------------------------------------------------------------

/*
    Parses a line of input (a string) for ';' and returns an array of strings 
*/
char ** get_cmd_line( char * line );

/*
    Parses a line of input (a string) for ' ' and returns an array of strings 
*/
char ** get_cmd_args(char * cmd);

/*
    Parses a pipe for '|', '>', or '<', and returns a two string array containing the piped or redirected commands
*/
char ** get_cmd_from_operator(char * line, char * operator);

/*
    Prints out an array of strings, given an array of strings (for testing)
*/
void print_string_arr(char ** arr);

//-----------------------------------------------------------------------------------------------------------------

//EXEC COMMANDS----------------------------------------------------------------------------------------------------

/*
    Executes pipe command given the two string array of the inputs
*/
void exec_pipe(char ** inputs);

/*
    Executes the ">" command given the two string array of the inputs
*/
void exec_redir_out(char ** inputs);

/*
    Executes the "<" command given the two string array of the inputs
*/
void exec_redir_in(char ** inputs);

/*
    Executes a simple command given the path and the arguments
*/
void exec_cmd(char * cmd, char ** args);

//-----------------------------------------------------------------------------------------------------------------