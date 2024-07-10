#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char** argv) {
	#if 0
		Address invalid inputs first
	#endif
	if (argc != 3) {
		fprintf(stderr, "ERROR: Invalid arguments\n");
		fprintf(stderr, "PROPER USE: a.out <n>, <filename>\n");
	}
	char* filename = *(argv+2);
	int number = atoi(*(argv+1));
	#if 0
		Check to see if number given is > 0, if not, error and EXIT_FAILURE
	#endif

	if (!(number >= 1)) {
		perror("Invalid number. Number input must be greater than 0.");
    	return EXIT_FAILURE;
	}
	#if 0
		Attempt to open the file
		if fileStatus == -1, file fails to open
	#endif
	int fileStatus = open(filename, O_RDONLY);
	if (fileStatus == -1) {
		perror("File failes to open.");
		return EXIT_FAILURE;
	}
	#if 0
		Use lseek to see the end of the file
	#endif	
	int eof = lseek(fileStatus, 0, SEEK_END);
	if (number > eof) {
		printf("\n");
		return EXIT_SUCCESS;
	}
	lseek(fileStatus, 0, SEEK_SET);

	while (eof > number) {
		char* buffer = malloc(number+1);
		read(fileStatus, buffer, number);
		*(buffer+number) = 0;
		printf("%s", buffer);
		if (eof - number - number >= number) {
			printf("|");
		}
		free(buffer);
		eof = eof - number - number;
		lseek(fileStatus, number, SEEK_CUR);
	}
	if (eof == number - 1) {
		printf("|");
		char* buf = malloc(number);
		read(fileStatus, buf, number-1);
		*(buf+number-1) = 0;
		printf("%s\n", buf);
		free(buf);
	}
	else {
		printf("\n");
	}
	close(fileStatus);
	return EXIT_SUCCESS;
}