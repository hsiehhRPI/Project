#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>

int validPlace(char** board, int x, int y, int length) {
	//Return values: -1 for not valid, returns the y coordinate of the valid placement
	//We don't need to check the entire board, just the rows before
	if (x == 0) {
		return y;
	}
	//Checking the column
	for (int i = 0; i < x; i = i + 1) {
		if (*(*(board+i)+y) == 'Q') {
			return -1;
		}
	}
	//Check left diagonal
	int mod = 1;
	while (x - mod >= 0 && y - mod >= 0) {
		if (*(*(board+x-mod)+y-mod) == 'Q') {
			return -1;
		}
		mod = mod + 1;
	}
	// Check right diagonal
	mod = 1;
	while (x - mod >= 0 && y + mod < length) {
		if (*(*(board+x-mod)+y+mod) == 'Q') {
			return -1;
		}
		mod = mod + 1;
	}
	return y;
}
void placeQueen(char** board, int x, int y, int col) {
	//Just place the queen
	*(board+x) = calloc(col, sizeof(char));
	*(*(board+x)+y) = 'Q';
}

int childPlanning(char** board, int row, int col) {
	//Returns the number of child to fork
	int nChild = 0;
	for (int v = 0; v < col; v = v + 1) {
		int vP = validPlace(board, row, v, col);
		if (vP != -1) {
			nChild = nChild + 1;
		}
	}
	return nChild;
}

void printBoard(char** board, int row, int col) {
	printf("Board display starts here\n");
	for (int n = 0; n < row; n = n + 1) {
		for (int i = 0; i < col; i = i + 1) {
			if (*(*(board+n)+i) == 'Q') {
			printf("Q");
			}
			else {
				printf("X");
			}
		}
		printf("\n");
	}
	printf("Board display ends here\n");
}

int child_process(char** board, int row, int col, int x, int y, int* pipefd) {
	close(*(pipefd+0));
	placeQueen(board, x, y, col);
	//printBoard(board, x+1, col);
	int n = 0;
	if (x+1 < row) {
		n = childPlanning(board, x+1, col);
	}
	if (n != 0) {
		#ifndef QUIET
			if (n == 1) {
				printf("P%d: %d possible move at row #%d; creating %d child process...\n", getpid(), n, x+1, n);
			}
			else {
				printf("P%d: %d possible moves at row #%d; creating %d child processes...\n", getpid(), n, x+1, n);
			}
		#endif
		//Collect the y coordinates
		//Fork the children
		//printf("Forking %d childrens\n", n);
		pid_t* pids = calloc(n, sizeof(pid_t));
		if (pids == NULL) {
			abort();
		}
		int counter = 0;
		int status;
		for (int i = 0; i < col; i = i + 1) {
			int yCoor = validPlace(board, x+1, i, col);
			if (yCoor != -1) {
				fflush(stdout);
				pid_t cp = fork();

				if (cp == -1) {
					abort();
				}
				if (cp == 0) {
					free(pids);
					return child_process(board, row, col, x+1, yCoor, pipefd);
				}
				#ifndef NO_PARALLEL
					waitpid(cp, &status, WNOHANG);
				#endif
				waitpid(cp, &status, 0);
				*(pids + counter) = cp;
				counter = counter + 1;
			}
		}
		//Okay parent process outside instead hopefully this works
		while (n > 0) {
			waitpid(-1, &status, 0);
			if (WIFSIGNALED(status)) {
				abort();
			}
			else if (WIFEXITED(status)) {
				free(pids);
				for (int i = 0; i < row; i = i + 1) {
					free(*(board+i));
				}
				free(board);
				free(pipefd);
				return EXIT_SUCCESS;
			}
			n--;
		}
		free(pids);
		for (int i = 0; i < row; i = i + 1) {
			free(*(board+i));
		}
		free(board);
		free(pipefd);
		return EXIT_SUCCESS;
	} else {
		if (x == row-1) {
			char* nQ = calloc(3, sizeof(char));
			sprintf(nQ,"%d",x+1);
			write(*(pipefd+1), nQ ,strlen(nQ));
			close(*(pipefd+1));
			free(nQ);
			#ifndef QUIET
				printf("P%d: found a solution; notifying top-level parent\n", getpid());
			#endif 
			for (int i = 0; i < row; i = i + 1) {
				free(*(board+i));
			}
			free(board);
			free(pipefd);
			return EXIT_SUCCESS;
		}
		else {
			char* nQ = calloc(3, sizeof(char));
			sprintf(nQ,"%d",x+1);
			write(*(pipefd+1), nQ ,strlen(nQ));
			close(*(pipefd+1));
			free(nQ);
			#ifndef QUIET
				printf("P%d: dead end at row #%d; notifying top-level parent\n", getpid(), x+1);
			#endif
			for (int i = 0; i < row; i = i + 1) {
				free(*(board+i));
			}
			free(board);
			free(pipefd);
			return EXIT_SUCCESS;
		}
	}
	//Managing return values of child processes
	//printf("Wait for my children to be done\n");
}
//Dont' want to do this but this is my ownly choice
int placeDex (char v) {
	if (v == '0') {
		return 0;
	}
	if (v == '1') {
		return 1;
	}
	if (v == '2') {
		return 2;
	}
	if (v == '3') {
		return 3;
	}
	if (v == '4') {
		return 4;
	}
	if (v == '5') {
		return 5;
	}
	if (v == '6') {
		return 6;
	}
	if (v == '7') {
		return 7;
	}
	if (v == '8') {
		return 8;
	}
	return 9;
}

//------------------------------ MAIN ----------------------------------
int main (int argc, char** argv) {
	
	//Get the inputs from command line
	//Check if there are enough arguments on the commandline
	if (argc != 3) {
		fprintf(stderr, "ERROR: Incorrect argument(s)\n");
		fprintf(stderr, "USAGE: hw2.out <m> <n>\n");
		return EXIT_FAILURE;
	}
	//Get the arguments from the commandline, check if they are greater than zero
	int m = atoi(*(argv+1));
	int n = atoi(*(argv+2));
	if (m < 1 || n < 1) {
		fprintf(stderr, "ERROR: Arguments must be at least 1\n");
		fprintf(stderr, "USAGE: hw2.out <m> <n>, m >= 1 && n >= 1\n");
		return EXIT_FAILURE;
	}
	if (m > n) {		//If n < m, swap them
		int tmp = m;
		m = n;
		n = tmp;
	}
	// Create pipeline!
	int* pipefd = calloc(2, sizeof(int));	//Allocate 2, for read and write
	int rc = pipe(pipefd);
	if (rc == -1) {
		fprintf(stderr, "ERROR: pipe() failed\n");
		abort();
	}
	// Create an empty board in the parent process, it will be copied to the children
	char** board = calloc(m, sizeof(char*));
	//Format printing for parent process, then create children process
	printf("P%d: solving the Abridged (m,n)-Queens problem for %dx%d board\n", getpid(), m, n);
	if (n == 1) {
		printf("P%d: %d possible move at row #0; creating %d child process...\n", getpid(), n, n);
	}
	else {
		printf("P%d: %d possible moves at row #0; creating %d child processes...\n", getpid(), n, n);
	}
	//Forking n children
	pid_t* pids = calloc(n, sizeof(pid_t));
	int status;
	if (pids == NULL) {
		fprintf(stderr, "ERROR: calloc() failed\n");
		abort();
	}
	for (int i = 0; i < n; i = i + 1) {
		fflush(stdout);
		pid_t cp = fork();
		if (cp == -1) {
			fprintf(stderr, "ERROR: fork() failed\n");
			abort();
		}
		if (cp == 0) {
			free(pids);
			return child_process(board, m, n, 0, i, pipefd);
		}
		*(pids + i) = cp;
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status)) {
			fprintf(stderr, "ERROR: calloc() failed\n");
			abort();
		}
		else if (WIFEXITED(cp)) {
			//Read pipe and record the number
		}
	}
	for (int i = 0; i < m; i = i + 1) {
		free(*(board+i));
	}
	free(board);
	free(pids);	
	printf("P%d: search complete\n", getpid());
	//Read from the pipe here, we must first determine the size of the contents in pipe
	close(*(pipefd+1));
	int* qCensus = calloc(m, sizeof(int));
	//This is just tiring I might as well just allocate a big string and read in info from the pipe
	char* chunk = calloc(1000, sizeof(char));
	read(*(pipefd+0), chunk, 1000);	
	int size = strlen(chunk);
	if (m < 10) {
		for (int i = 0; i < size; i = i + 1) {
			int num = placeDex(*(chunk+i));
			*(qCensus+num-1) = *(qCensus+num-1) + 1; 
		}
	}
	if (m >= 10 && m < 100) {
		for (int i = 1; i < size; i = i + 1) {
			int num = placeDex(*(chunk+i-1));
			int num2 = placeDex(*(chunk+i));
			int sum = 10*num + num2;
			if (sum <= m) {
				*(qCensus+sum-1) = *(qCensus+sum-1) + 1; 
			}
			else {
				*(qCensus+num-1) = *(qCensus+num-1) + 1;
			}
		}
	}
	if (m >= 100) {
		//You can definitely place at least 10 
		for (int i = 2; i < size; i = i + 2) {
			int num = placeDex(*(chunk+i-2));
			int num2 = placeDex(*(chunk+i-1));
			int num3 = placeDex(*(chunk+i));
			int sum = 100*num + 10*num2+num3;
			int sum2 = 10*num + num2;
			if (sum <= m) {
				*(qCensus+sum-1) = *(qCensus+sum-1) + 1; 
			}
			else {
				*(qCensus+sum2-1) = *(qCensus+sum2-1) + 1;
			}
		}
	}
	free(chunk);	//Huge mem alloc, just get rid of it
	//Now that the whole ordeal is over, output them!
	for (int i = 0; i < m; i = i + 1) {
		printf("P%d: number of %d-Queen end-states: %d\n", getpid(), i+1, *(qCensus+i));
	}
	free(qCensus);
	free(pipefd);
	return EXIT_SUCCESS;
}
