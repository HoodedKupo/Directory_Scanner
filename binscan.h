/*
 * binscan.h
 * written by: Nathan Koop
 *
 * description:
 *     contains the function signatures for all functions
 *     used in the binscan.c file
 */

#include <stdio.h>
#include <dirent.h>

/*
 * is_ELF
 * description:
 *     checks if the file passed is an elf file
 *     this is done by checking if the first 4 bytes are the "elf_magic"
 *     IE: 0x464c457f
 * parameters:
 *     fptr: a pointer to a FILE type. The file to check elf status of
 * returns:
 *     0: if the file is not an elf file
 *     1: if the file is an elf file
 * pre-condition:
 *     fptr is initialized
 */
int is_ELF(FILE *fptr);

/*
 * read_first_line
 * description:
 *     opens the specified file and reads the first line of the file
 * parameters:
 *     file_path: a string of the path of the file to get the first line of
 * returns:
 *     a string containing the first line of the file
 *     or "a" if the file does not exist.
 * pre-conditions:
 *     file_path is initialized.
 */
char *read_first_line(char *file_path);

/*
 * get_digits
 * description:
 *     calculated the number of digits in the given positive number
 * parameters:
 *     i: the positive number to find the number of digits of
 * returns:
 *     the number of digits in the number i
 * pre-conditions:
 *     i>=0
 */
int get_digits(int i);

/*
 * int_to_string
 * description:
 *     converts the given positive integer into a string
 * parameters:
 *     value: positive integer to convert to string
 * returns:
 *     string representation of the value
 * pre-conditions:
 *     value>=0
 * post-conditions:
 *     memory block allocated for length of string.
 */
char *int_to_string(int value);

/*
 * display_result_line
 * description:
 *     pads the value such that the number is right-justified then displays
 *     the rest of the output line as indicated by the user
 * parameters:
 *     spaces: the max number of spaces.
 *             or the column to right-justify value to
 *     value: the number to be displayed on this line
 *     prompt: the trailing sentence for this line
 * pre-condition:
 *     value>=0
 *     prompt is initialized
 *     spaces>=0
 */
void display_result_line(int spaces, int value, char *prompt);

/*
 * disp_res
 * description:
 *     displays the amount of each file type that was found in the
 *     directory that was specified when this program was called.
 * parameters:
 *     spcs: the column to right-justify each value to.
 *     elf: the number of elf files found.
 *     prl: the number of perl files found.
 *     shl: the number of shell files found.
 *     py: the number of python files found.
 *     ruby: the number of ruby files found.
 *     oth: the number of other files found.
 * pre-conditions:
 *     all parameters are greater than or equal to zero.
 */
void disp_res(int spcs, int elf, int prl, int shl, int py, int ruby, int oth);

/*
 * read_files
 * description:
 *     reads through all files in the directory and determines their file type
 *     it then calls various helper functions
 *     to display this information to the user.
 * parameters:
 *     directory: pointer to a DIR file of the search directory.
 *     dir_name: a string containing the name of the directory.
 * pre-condition:
 *     directory is initialized and a valid DIR object.
 *     dir_name is initialized.
 */
void read_files(DIR *directory, char *directory_name);
