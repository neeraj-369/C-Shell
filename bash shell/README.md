The executable is ./shell

HOW TO RUN :- 1. first run make
              2. execute by ./shell

My shell will run same as bash terminal which runs foreground process and background process, also commands like cd, ls, pwd, echo, repeat, pinfo, etc..
i made a makefile using all the .c files, main.c, headers.c
all the .c files are:

bg.c : it runs the given commands in background process and works well with error handling
cd.c : it runs same as the cd command on terminal with all the flags and commands
echo.c : it runs the same as echo on terminal and prints
fg.c : it runs the commands on foreground and executes them
my process will even execute and run executable files
pinfo.c : it prints the information required accordingly as asked in pdf
repeat.c : it performs repeat operation on the command given works well.
i also made sleep to run in background.
i haven't used any execvp command for the commands mentioned in the question paper.
BONUS : I MADE HISTORY COMMAND AND ALONG WITH HISTORY INT BOTH THE HISTORY COMMANDS AND EVERYTHING WORKS FINE. (history.c)


TO exit the shell :- enter "quit" and press enter.