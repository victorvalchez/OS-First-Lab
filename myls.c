#include <stdio.h>            // Header file for printf. 
#include <unistd.h>		      // Header file for system call getcwd.
#include <sys/types.h>		  // Header file for system call open.
#include <dirent.h>
#include <string.h>                



int main(int argc, char *argv[]){
    
    // Declaration of the variables that the function will use.
    DIR *direction;
    // Read is the pointer of the next file in the directory.
	struct dirent *read;

	// If it only recieves an argument (name of the program) it takes the current directory.
    if (argc < 2) {
        // Declaration of the buffer with the maximum size.
		char buff_dir[PATH_MAX];
        // We use getcwd with the buffer and the maximum path.
		getcwd(buff_dir, PATH_MAX);
        // Open the current directory.
		direction = opendir(buff_dir);
	}
    //If it receives more than an argument, it takes just the first argument.
	else {
        //Open the directory of the passed parameter.
		direction = opendir(argv[1]);
	}

    //If the returned direction is NULL it means it couldn't be opened.
	if (direction == NULL) {
		printf("Could not open the directory \n");
		return -1; 
	}
    
    //Make a loop to read all files and print them until getting NULL (all have been read).
    while ((read = readdir(direction)) != NULL) {
        printf("%s\n", read -> d_name);
    }

    // Check for errors while closing the directory.
	if ((closedir(direction)) < 0) {
        printf("Error while closing the directory. \n");
        return -1;
    }

    // Stop program successfully.
	return 0;
    
}
