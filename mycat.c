#include <stdio.h>            // Header file for printf. 
#include <sys/types.h>		  // Header file for system call  open. 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		      // Header file for system calls read, write y close.

#define BUFFER_SIZE 1024



int main(int argc, char *argv[]) {
    
    // Declaration of the variables that the function will use.
    // Declaration of the file descriptor.
    int descriptor;
    // Declaration of the buffer --> Vector with length equal to the BUFFER_SIZE.
    char buffer[BUFFER_SIZE];
    // Declaration of the variable that stores the number of bytes to read.
    int nread;
	
    // If the number of arguments is less than two we print the error and return.
	if (argc < 2) {
		printf("Not enough arguments. \n");
		// Stop program.
        return -1;
	}
    
    // Open the file, save its descriptor and check it to see if there is an error. The system call 'open' is used.
    descriptor = open(argv[1], O_RDONLY);
    // If descriptor is equal to -1 there is no such file (error), so the function will end.                       
    if (descriptor < 0) {                                           
        printf("The file does not exist. \n");
        // Stop program.
        return -1;
    }
    
    /* The number of bytes to read are stored in the declared variable.The system call
    'read' is used. Until the buffer is empty (or error), the information of the file
    is written. The system calls 'write' and 'read' are used. */
    while ((nread = read(descriptor, buffer, BUFFER_SIZE)) > 0) {
        // Check if there is an error while writing.
        if (write(STDOUT_FILENO, buffer, nread) < nread) {
            // Check if there is an error while closing the descriptor. System call 'close' is used.
			if (close(descriptor) < 0) {
                printf("Error while closing the descriptor.");
                // Stop program.
                return -1;
            }
            printf("Error while writing.");
			 // Stop program.
            return -1;
		}
    }

    // Check if there is an error while reading from the file.
    if (nread < 0) {
        printf("Error while reading.");
        // Check if there is an error while closing the descriptor. System call 'close' is used.
        if (close(descriptor) < 0) {
            printf("Error while closing the descriptor.");
            // Stop program.
            return -1;
        }
    }

    // Check if there is an error while closing the descriptor. System call 'close' is used.
	if (close(descriptor) < 0) {
        printf("Error while closing the descriptor.");
        // Stop program.  
        return -1;
    }

    // Stop program successfully.
    return 0;

}
