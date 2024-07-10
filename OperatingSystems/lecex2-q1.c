#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int lecex2_child(unsigned int n) {
	if (n < 1) {
		fprintf(stderr, "Error: Cannot read negative indices, input should be at least 1.\n");
		abort();
	}
	//Read from file lecex2.txt
	int fd = open("lecex2.txt", O_RDONLY);
	//Check for fd condition
	if (fd == -1) {
		fprintf(stderr, "Error: File failes to open, check if file exists or spelling of input filename.\n");
		abort();
	}
	//Check if nth character actually exists
	int totalChars = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (totalChars == 0) {
		fprintf(stderr, "Error: Input file is empty.");
		abort();
	}
	if (n > totalChars||n < 1) {
		fprintf(stderr, "Error: Input is less than 1 or file size smaller than input number specified.\n");
		abort();
	}
	//Perform the child process
	char* buf = calloc(1, sizeof(char));
	//Use lseek to find the correct character to read
	lseek(fd, n-1, SEEK_SET);
	read(fd, buf, 1);
	if (*(buf+0) == '\r') {
		fprintf(stderr, "Error: Character read is carriage return, will mess up parent return line format.\n");
		abort();
	}
	char res = *(buf+0);
	free(buf);
	close(fd);
	return res;
}

int lecex2_parent() {
	//Use waitpid
	int stat;
	pid_t child_pid = waitpid(-1, &stat ,0);
	if (WIFSIGNALED(stat)) {
		//Child process terminated abnormally
		//Check if process got aborted?
		printf("PARENT: child process terminated abnormally!\n");
		return EXIT_FAILURE;
	}
	else if (WIFEXITED(stat)) {
		//Child process terminated successfully
		printf("PARENT: child process returned '%c'\n", WEXITSTATUS(stat));
		return EXIT_SUCCESS;
	}
	return child_pid;
}