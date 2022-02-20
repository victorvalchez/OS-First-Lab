#include <stdio.h>		                    /* Header file for printf. */
#include <sys/types.h>		                /* Header file for system call  open. */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		                    /* Header file for system calls read, write y close. */

#define BUFFER_SIZE 1024    // 1024 bytes

/*
The first program, mycat will open the file specified by argument and will show its content
through standard output (the console) using the calls open, read, write and close. For this
purpose:
• It will open the file specified as parameter with open.
• It will read the contents of the file using an intermediate buffer of 1024 bytes (read).
• It will write (write) the content of the buffer in the standard output. Use the constant STDOUT FILENO as value of the         descriptor to write to the standard output. 
• Finally, it will close the descriptor using close.
*/

int main(int argc, char *argv[]) {
    
    int descriptor;
    char buffer[BUFFER_SIZE];
    int nread;
  
	/* If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print the error and return -1. */
	if(argc < 2) {
		printf("Not enough arguments. \n");
        // Stop program.
		return -1;
	}
    
    //Open the file, save its descriptor and check it to see if there's an error
    descriptor = open(argv[1], O_RDONLY);
    if (descriptor < 0) {
        printf("The file doesn't exist. \n");    // If descriptor is equal to 0 there's no such file.
        return(-1);
    }
    else{
        nread = read(descriptor, buffer, BUFFER_SIZE);
        if (nread != 0) {
            do {
                write(STDOUT_FILENO, buffer, nread);
                nread = read(descriptor, buffer, BUFFER_SIZE);
            }
            while(nread != 0);
        }
    }
    close(descriptor);  
    return 0;
}

/*
// The file cannot be opened.
if ((infile = open(name, O_RDONLY)) < 0) {
    return(-1);
}
*/

/*
The predefined descriptors are:
    •	0 : Standard input (read from stdin).
    •	1 : Standard output (write to stout).
    •	2 : Error output (write to stderr).
*/
