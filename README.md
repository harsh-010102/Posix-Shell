
#  AOS Assignment - 2




# Task   1

## Functionality 
- Whenever the code gets executed, system information should be display like shell prompt.
- The directory from which the shell is invoked will be the home directory of the shell and should be indicated by "~".
- Whenever the code runs it will be running a loop continually with the system information and username and it should also handle the commands given as input.


## Corresponding File and System Call 
- start.cpp
- getHostName()
- getcwd()

# Task 2
## Functionality
- cd will change current working directory to the given input directory.
- echo will print given input to console as it is.
- pwd will print the path of the current working directory.

## Handled Cases:
```
- cd .
- cd ..
- cd ~
- cd <path>
- cd -.
```
##Corresponding File and System Call
- helper.cpp
- chdir()
- getcwd()

# Task  3
## Functionality
-  List all files and directories for current working directory.
- List  all details of mentioned files or directories.
- It supports both relative and absolute path.
- Flag "-l" will give all information like permissions, total-links, username, groupname, size, last modified date and name.
- Flag "-a" will display all files including hidden files.

## Handled Cases :

```
- ls
- ls -a
- ls -l
- ls .
- ls ..
- ls ~
- ls -a -l
- ls -la / ls -al
- ls <Directory/File_name>
- ls -<flags> <Directory/File_name>
```
## Corresponding File and System call 
- lscomm.cpp
- lstat()
- opendir()


# Task  4
## Functionality

### Background
-  Any command invoked with "&" at the end of syntax will be treated as background process.
- It will create child process and will not force parent process to wait until child process ends so we can use terminal even if there is some background running.

```
    <command> &
```
###Foreground
- Except ls, pwd, echo, cd, pinfo commands all other commands will run as Foreground process which is handled by execvp system call.
## Handled Cases :

```
    <command>
```

## Corresponding File and System call 

- process.cpp
- fork()
- execvp()

# Task 5
## Functionality
- Prints process related info like Process-id, Status, Virtual Memory usage and executable path.
## Handled Cases:
- pinfo
- pinfo <Process-id>

## Corresponding File and System call 

- process.cpp
- fopen()

# Task 6
## Functionality
- Search command will search for a specific file or directory from the current working directory in recursive manner.
- It returns true if file exists otherwise returns false.
## Handled Cases
```
search <file-name/directory-name>
```
## Corresponding File and System call 
- my_search_file.cpp
- lstat()
- readdir()

# Task 7
## Functionality
-  Supports input and output redirection using the symbols <, >, and >>. It allows you to redirect the output of commands to a file, read input from a file, or both.
- For input redirection (<), the shell reads from the specified file as input for the command.
- For output redirection (> and >>), the shell creates or appends to the specified file and directs the command's output to that file.
- The shell handles errors appropriately:
- Displays an error message if the input file does not exist.
- Creates the output file with permissions 0644 if it doesn't exist for > and appends to it for >>.

## Corresponding File and System Call
- redirection.cpp()
- open()
- close()
- dup2()
- fork()
- execvp()
- waitpid()


## Task 12
#Funcrionality
- Implement history command just like terminal.
- History should keep track of the commands across all sessions and not just one.

## Handled Cases
```
 - history
- history <num>
```

## Corresponding File and System Call
history_file.cpp
