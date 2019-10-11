************************************************************************************
* RENFA ****************************************************************************
************************************************************************************
Author: Dwayne Butler
Saanail.Vernath@gmail.com


************************************************************************************
* Description **********************************************************************
************************************************************************************
This program converts a regular expression into an NFA. 
It takes either a file with regular expressions in it (separated by newlines) or reads from stdin.
Regular expressions must be in POSTFIX form and use the symbols a, b, c, d, e, E, &, *, or |.
a, b, c, d, e, and E are the language of the NFA.
& is the concatenate operation.
| is the union operation.
* is the kleene star operation.
q will exit the program.

The program generates the NFA piece by piece by reading the string and passing each part of the string to an nfa creator.
The nfa creator generates a basic nfa if a letter is passed or uses nfas on the stack to use an operator.
At the end it prints a table to show the transitions of the final nfa.
If nothing is passed, it just shows the very basic nfa with an empty string transition.


************************************************************************************
* Compile and Run ******************************************************************
************************************************************************************
To compile in command line(on linux):

tar -xvf dbutlerRenfa.tar

make


To run after compiling:
./renfa <filename>

OR

./renfa
<enter RE into command line>


************************************************************************************
* Files ****************************************************************************
************************************************************************************
Each file below has more detailed comment descriptions within them if you want to know more.

README.txt   Readme file. You're here!
Makefile     Standard makefile to compile easily (in linux)
renfa.h      Combined header file. Includes the structs the program uses.
stack.c      Stack functions, including allocator, push, and pop functions.
reNfa.c      Main function. Includes main and the supporting functions to read the RE and pass it to the nfa creator.
list.c       Transition list tools. Includes functions to allocate and manipulate list structures.
nfa.c        NFA creation tools. Includes functions to allocate, concatenate, union, and kleene star NFAs as well as their supporting functions.
print.c      Table printer functions and a debugger function to see the whole stack. (Debugger function is only called if DEBUG is set to 1 or 2 in renfa.h)
memFree.c    Memory allocation freeing functions (primarily used to free the list from the nfa)


************************************************************************************
* Debugger (default 0) *************************************************************
************************************************************************************
Change DEBUG to 2 to see the debug printout and the table printout.
Change DEBUG to 1 to see only the debug printout.
Change DEBUG to 0 (default) to have the program work normally.

