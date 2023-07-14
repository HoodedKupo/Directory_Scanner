/*
 * binscan
 * written by: Nathan Koop
 *
 * description:
 *     the executable takes a directory as its first and only
 *     command line argument.
 *     if no directory is passed then the ussage is displayed to the user.
 *     if an invalid directory is passed then the user is alerted as such.
 *     if a valid directory is passed then the program counts
 *     the number of each file: elf, perl, shell, python, ruby, and other.
 *     then displays the count of each to the user.
 */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "binscan.h"

//the maximum characters in a line
int MAXLINE = 100;

/*
 * main
 * description:
 *     the function that is called when the executable is run.
 *     is responsible for calling various functions in order for the program to
 *     execute properly and with correct behavior.
 * parameters:
 *    argc: the number of command line arguments
 *    argv[]: an array of strings representing the command line arguments.
 * returns:
 *     1: if execution failed.
 *     0: if execution did not fail.
 */
int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("USAGE: binscan <directory>\n");
		return 1;
	}
	DIR * dirptr = opendir(argv[1]);

	if (dirptr == NULL) {
		printf("binscan: No such directory \"%s\"\n", argv[1]);
		return 1;
	}
	read_files(dirptr, argv[1]);
	closedir(dirptr);
	return 0;
}

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
int is_ELF(FILE *fptr)
{
	int *elf_magic = malloc(sizeof(int)*1);
	int size = fread(elf_magic, sizeof(int), 1, fptr);

	if (size != 1) {
		free(elf_magic);
		return 0;
	}
	if (*elf_magic == 0x464c457f) {
		free(elf_magic);
		return 1;
	}
	free(elf_magic);
	return 0;
}

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
char *read_first_line(char *file_path)
{
	FILE *fptr = fopen(file_path, "r");

	if (fptr == NULL)
		return "a";
	char *scanner = malloc(1);
	char *line = malloc(MAXLINE);
	int index;
	int read_items = fread(scanner, 1, 1, fptr);

	index = 0;
	while (*scanner != '\n' && index < MAXLINE-1 && read_items == 1) {
		line[index] = *scanner;
		index++;
		read_items = fread(scanner, 1, 1, fptr);
	}
	free(scanner);
	line[index] = '\0';
	fclose(fptr);
	free(file_path);
	return line;
}

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
int get_digits(int i)
{
	if (i == 0)
		return 1;
	int d = 1;
	int digits;

	digits = 0;
	while (i/d >= 1) {
		d = d * 10;
		digits += 1;
	}
	return digits;
}

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
char *int_to_string(int value)
{
	if (value == 0) {
		char *zero = malloc(2);

		zero[0] = '0';
		zero[1] = '\0';
		return zero;
	}

	int digits = get_digits(value);
	char *return_value = malloc(digits+1);
	int index;

	index = 0;
	while (value > 0 && index < digits) {
		int i = value % 10;
		char c = '0' + i;

		return_value[index] = c;
		index++;
		value -= i;
		value = value / 10;
	}

	//reverse string
	int ptrl;
	int ptrr = digits-1;

	ptrl = 0;
	while (ptrl < ptrr) {
		char temp = return_value[ptrl];

		return_value[ptrl] = return_value[ptrr];
		return_value[ptrr] = temp;
		ptrl++;
		ptrr--;
	}

	return_value[digits] = '\0';
	return return_value;
}

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
void display_result_line(int spaces, int value, char *prompt)
{
	int d_value = spaces - get_digits(value);

	if (d_value < 0)
		d_value = 0; //this will break the allignment
	int i;

	i = 0;
	for (i = 0; i < d_value; i++)
		printf(" ");
	char *s_value = int_to_string(value);

	printf("%s %s", s_value, prompt);
	free(s_value);
}

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
void disp_res(int spcs, int elf, int prl, int shl, int py, int ruby, int oth)
{
	display_result_line(spcs, elf, "ELF executable\n");
	display_result_line(spcs, prl, "Perl script\n");
	display_result_line(spcs, shl, "Shell script\n");
	display_result_line(spcs, py, "Python script\n");
	display_result_line(spcs, ruby, "Ruby script\n");
	display_result_line(spcs, oth, "Unknown programs\n");
}

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
void read_files(DIR *directory, char *dir_name)
{
	struct dirent *entry;
	int elfs, perls, shells, pythons, rubys, others;

	perls = 0;
	shells = 0;
	pythons = 0;
	rubys = 0;
	others = 0;
	int dir_length = strlen(dir_name);

	while ((entry = readdir(directory))) {

		int b;
		char *path = malloc(strlen(entry->d_name)+strlen(dir_name)+2);

		b = 0;
		strncpy(path, dir_name, dir_length);
		path[dir_length] = '/';
		path[dir_length+1] = '\0';
		strncat(path, entry->d_name, strlen(entry->d_name));
		FILE *fptr = fopen(path, "r");

		free(path);
		if (fptr == NULL) {

		} else {
			if (is_ELF(fptr) == 1) {
				elfs += 1;
				b = 1;
			}
		fclose(fptr);
		}

		//read first line
		char *path2 = malloc(strlen(entry->d_name)+strlen(dir_name)+2);

		strncpy(path2, dir_name, dir_length);
		path2[dir_length] = '/';
		path2[dir_length+1] = '\0';
		strncat(path2, entry->d_name, strlen(entry->d_name));
		char *line = read_first_line(path2);

		if (strstr(line, "sh") != NULL) {
			shells++;
			b = 1;
		} else if (strstr(line, "bash") != NULL) {
			shells++;
			b = 1;
		} else if (strstr(line, "zsh") != NULL) {
			shells++;
			b = 1;
		} else if (strstr(line, "csh") != NULL) {
			shells++;
			b = 1;
		} else if (strstr(line, "python") != NULL) {
			pythons++;
			b = 1;
		} else if (strstr(line, "python3") != NULL) {
			pythons++;
			b = 1;
		} else if (strstr(line, "perl") != NULL) {
			perls++;
			b = 1;
		} else if (strstr(line, "ruby") != NULL) {
			rubys++;
			b = 1;
		}
		if (b == 0)
			others++;
		free(line);
	}
	disp_res(8, elfs, perls, shells, pythons, rubys, others);
}
