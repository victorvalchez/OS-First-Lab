#include <stdio.h>		                    // Header file for printf. 
#include <sys/types.h>		                // Header file for system call  open. 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		                    // Header file for system calls read, write y close.

#define BUFFER_SIZE 1024                    // 1024 bytes.


int main(int argc, char *argv[]) {
    
    // Declaration of the variables the function will use.
    int descriptor;             // Declaration of the file descriptor.
                                                 
    char buffer[BUFFER_SIZE];   // Declaration of the buffer --> Vector with length equal to the BUFFER_SIZE.
    
    int nread;                  // Declaration of the variable that stores the number of bytes to read.
  
	// If the number of arguments is less than two we print the error and return.
	if(argc < 2) {
		printf("Not enough arguments. \n");
        // Stop program.
		return(-1);
	}
    
    // Open the file, save its descriptor and check it to see if there is an error. The system call 'open' is used.
    descriptor = open(argv[1], O_RDONLY);
    // If descriptor is equal to -1 there is no such file (error), so the function will end.                       
    if (descriptor < 0) {                                           
        printf("The file does not exist. \n");                       
        return(-1);
    }
    
    // The bytes to read are stored in the declared variable. The system call 'read' is used.
    nread = read(descriptor, buffer, BUFFER_SIZE);
    
    if(nread = read(descriptor, buffer, BUFFER_SIZE) < 0) {
            printf("Error while reading");
            return(-1);
        }

    // Until the buffer is empty, the information of the file is written. The system calls 'write' and 'read' are used.
    do {
        write(STDOUT_FILENO, buffer, nread);
        nread = read(descriptor, buffer, BUFFER_SIZE);      // Variable nread stores the bytes effectively read
    } while(nread != 0);
    

    // Closes and returns 0. The system call 'close' is used.
    close(descriptor);                                              
    return 0;
}

