# Directory_Scanner
Scans all files in a directory and counts the number of each filetype.
## Files
The binscan.c file is the main file that contains the logic of the program.\
binscan.h is the header file that contains the function signatures for the binscan.c file.\
makefile is a file used to compile the program, see "How To Use".\
the README file contains usefull information about the software.
## Description
the executable takes a directory as its first and only command line argument.\
if no directory is passed then the ussage is displayed to the user.\
if an invalid directory is passed then the user is alerted as such.\
if a valid directory is passed then the program counts the number of each file:\
elf, perl, shell, python, ruby, and other.\
these files are determined by looking at the contents of the file instead of trusting the file extension (which users can change).\
then displays the count of each to the user.
## How To Use
First type the command "make" in order to compile the executable.\
Next call the function and pass a directory name as a command line argument. For example "binscan <directoryName>"\
the program will display the number of each file type if the provided directory exists.\
Once you're done run "make clean" to remove the executable file.

