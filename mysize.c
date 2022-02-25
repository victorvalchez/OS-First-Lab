#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

#define PATH_MAX 32768

int main(int argc, char *argv[]){
    DIR *direction;
	struct dirent *read;
	int descriptor;
    char currentDir[PATH_MAX];                                             // Create buffer.
	getcwd(currentDir, PATH_MAX);                                          // Get the current path in currentDir.
	direction = opendir(currentDir);                                       // Open the directory.
    
	if(direction == NULL) {                                                // If the direction is NULL the directory has not been opened.
		printf("If direction is NULL, the directory could not be opened");
		return -1;
	}
    else {
		read = readdir (direction);                                         // It reads the files of the directory.
		while(read != NULL) {                                               // While a file is read, the loop continues.
			long size = 0;
            if(read -> d_type == DT_REG) {                                  // If the file is a regular file print its name and size.
                                                                            // Las position of the same size and that prints the name and size of the file.
                descriptor = open(read -> d_name,O_RDWR);   
                size = lseek(descriptor, 0L, SEEK_END);
                printf("%s\t%ld\n", read -> d_name, size);  
                close(descriptor);                                          // Close file.
            } 
			read = readdir (direction);
		}
	}
	closedir(direction);                                                     // Close the directory when finished.
	return 0;
}
