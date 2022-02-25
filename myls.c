#include <stdio.h>		        /*Cabecera llamada al sistema printf*/
#include <unistd.h>		        /*Cabecera llamada al sistema getcwd*/
#include <sys/types.h>		    /*Cabeceras llamadas al sistema opendir, readdir y closedir*/
#include <dirent.h>
#include <string.h>

#define PATH_MAX 32768

int main(int argc, char *argv[]){
	DIR *direction;
	struct dirent *read;			    // Read is the pointer of the next file in the directory

	// If you dont pass a directory, it does the ls function of the current directory
    
	if (argc < 2) {		            //If it only recieves an argument (name of the program) it takes the current directory
		char dirActual[PATH_MAX];	//Create the buffer with the maximum size
		getcwd(dirActual, PATH_MAX); // We use getcwd with the buffer and the maximum path
		direction = opendir(dirActual); // Open the current directory
		}
	else {	//If it receives more than an argument, it takes the first argument 
		direction = opendir(argv[1]); //Open the directory of the passed parameter
		}

    
	if(direction == NULL) { //If the returned direction is NULL it means it couldn't be opened
		printf("Could not open de directory \n");
        //exit(-1)
		return -1; 
	}
    //Make a loop to read all files and print them until you get NULL meaning all have been read
    else {
			read = readdir(direction);
			while(read != NULL) {
			printf("%s\n", read -> d_name);
			read = readdir(direction);
			}
		}
		closedir(direction);
	return 0;
}
