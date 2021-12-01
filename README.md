# Systems Project 01 - PeteSteveShell (PSHell)
### By Steven Lei and Peter Zhao
  

[Basic implementation of a shell.](https://www.stuycs.org/systems-dw/2021/11/17/p01.html)

  

## Features

  
* run bash commands
* `exit` to close the shell
* `cd` to change directories
* run multiple commands in one line using `;`
* two argument piping using ` | `
* basic redirection using `<` and `>`
* `color` to display working directory with color of choosing 
* `size_set` to set the number of bytes allocated for command input


## Usage

  For command inputs, please limit to one space before and after the `;`, `|`, `<`, `>`e.g
  ```c
  # ls -a;echo hi   //works
  # ls -a ; echo hi //works
  # ls -a; echo hi  //works
  # ls -a ;echo hi  //works
  ```
  
  You can edit the printed working directory color by using the custom command `color` using the arguments "blue", "green", or "red".

  ```c
  # color blue //changes directory color to blue
  # color red //changes directory color to red
  # color green //changes directory color to green
  # color brown //Displays message "Invalid Color. Try 'blue', 'green', or 'red'."
  ```  

  You can use the custom command `set_size` with an integer argument to specify the number of btyes needed to store your command input. Argument values less than 1 are rejected.

  ```c
  # set_size 750
  Input size set to 750 bytes.
  # set_size -2
  Invalid size.
  ```

## Attempts

We tried to implement the 'and' operator, `&&`, which is built into the Linux shell. `&& ` is supposed to execute the second command only if the execution command succeeds. However, we ran into problems checking the execution status of each command since using execvp ends each process. If we had more time, we would try to use popen and the error feedback it has to see whether or not the execution was successful to implement this operator. 

## Bugs

An issue that may appear in testing of this project would be the input size. In order to scan in the command line input from the shell, we pre-set a string with default size of 500 bytes. If the input size exceeds this value, the expected output will not be achieved. To alleviate this, we have created a `set_size` command that allows one to set a custom size for his/her input if the input is extremely large.

We also restricted the byte size to the output that is read in for our piping command to 7500 bytes. If the output of the input function exceeds this amount, the data will be cut off and will thus be lost. As a result, the function being piped to will not receive the right input and may not produce the expected output or execute properly.

## Function Headers

```c

//SETUP COMMANDS--------------------------------------------------------------------------------------------------

/*
    Prints the current working directory in the given color
*/
void pwd(char color);

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
```

