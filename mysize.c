#include <stdio.h>            // Header file for system call printf.
#include <sys/types.h>	      // Header file for system call fstat.
#include <sys/stat.h>
#include <fcntl.h>	          // Header file for system call fcntl.
#include <dirent.h> 	      // Header file for system call opendir, closedir, readdir...
#include <unistd.h>



int main(int argc, char *argv[]){

    struct dirent *read;
    int descriptor;
    DIR *direction;
    // Create buffer.
    char buff_dir[PATH_MAX];

    if (argc >= 2) {
        printf("Too many arguments. \n");
        return -1;
    }

    // Get the current path in buff_dir.
    getcwd(buff_dir, PATH_MAX);
    // Open the directory.
	direction = opendir(buff_dir);

    // If the direction is NULL the directory has not been opened.
	if(direction == NULL) {
		printf("Could not open the directory. \n");
		return -1;
	}

    // It reads the files of the directory.
    read = readdir(direction);
    // While a file is read from the directory, the loop continues.
    while(read != NULL) {
        // Declaration of a variable to store the offset returned by lseek.
        int size = 0;
        // If the file is a regular file print its name and size.
        if(read -> d_type == DT_REG) {
            descriptor = open(read -> d_name, O_RDONLY);
            if (descriptor < 0) {                                           
                printf("The file could not be opened. \n");
                // Stop program.
                return -1;
            size = lseek(descriptor, 0, SEEK_END);
            if (size < 0) {                                           
                printf("Error while obtaining size. \n");
                // Stop program.
                return -1;
            // The name and size are printed separated by four single spaces.
            printf("%s    %d\n", read -> d_name, size);  

            // Check for errors while closing the directory.
        	if ((close(descriptor)) < 0) {
                printf("Error while closing the descriptor. \n");
                return -1;
            }
        } 
        // It continues reading the files of the directory.
        read = readdir(direction);
    }
	
	// Check for errors while closing the directory.
	if ((closedir(direction)) < 0) {
        printf("Error while closing the directory. \n");
        return -1;
    }

    // Stop program successfully.
    return 0;
    
}
