#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

	/*If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print 	 the error and return -1*/
	if(argc < 2)
	{
		printf("Not enough arguments\n");
		return -1; /* Stop program*/
	}
	printf("%s\n", argv[1]); /* Print the file name */
	int fichero = open(argv[1], O_RDONLY); /* open the file in read only mode*/
	if (fichero < 1){ 	/* If the readed file showed no problems we continue*/
		printf("El fichero selecionado no existe\n");
		return -1; 	/* Stop program*/
	}
	char guardado[BUFFER_SIZE];  /*Var to save the readed file*/
	int leido = read(fichero, guardado, BUFFER_SIZE); /*Read the file and check errors*/
	while (leido >0){
		write(STDOUT_FILENO, guardado, leido);  /*WHile there is smth left to read keep going*/
		leido = read(fichero, guardado, BUFFER_SIZE); /*update the read once we rode the first 1024 Bytes*/
	}
	if (leido >= 0){
		close(fichero);	/* If correctly read close the opened file*/
	}
	return 0;
	}

