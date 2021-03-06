# Systems Project 01 - PeteSteveShell (PSHell)
### By Steven Lei and Peter Zhao
  

[Basic implementation of a shell.](https://www.stuycs.org/systems-dw/2021/11/17/p01.html)

  

## Features

  
* run bash commands
* `exit` to close the shell
* `cd` to change directories
* run multiple commands in one line using `;`
* single pipe, two argument piping using ` | `
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
  # ls -a   ;echo hi // does not work
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

We tried to implement beyond single pipe - piping (e.g. `a | b | c`); however, we weren't able to get this to function properly with our given code flow. Our current code flow detects piping by checking if the input is in some form of `a | b` and then executes the piping commands. We don't detect for an abirtrary amount of piping sequences. If we were to make chained piping, there wouldn't be a way for us to resolve a pipe sequence, return the output, and then input it into the next pipe sequence. 

This also the same case for multiple redirects.

## Bugs

An issue that may appear in testing of this project would be the input size. In order to scan in the command line input from the shell, we pre-set a string with default size of 500 bytes. If the input size exceeds this value, the expected output will not be achieved. To alleviate this, we have created a `set_size` command that allows one to set a custom size for his/her input if the input is extremely large.

We also restricted the byte size to the output that is read in for our piping command to 7500 bytes. If the output of the input function exceeds this amount, the data will be cut off and will thus be lost. As a result, the function being piped to will not receive the right input and may not produce the expected output or execute properly.

## Function Headers

```c

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
```

