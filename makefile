#Establish the makefile variables
CC = gcc-10
CFLAGS = -Wall

#creates the binscan executable
binscan: binscan.c binscan.h
	$(CC) $(CFLAGS) $^ -o $@
	chmod -cf 777 ./$@

#removes all executable files
clean:
	rm binscan
