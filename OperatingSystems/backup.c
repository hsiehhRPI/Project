int placeQueen(char** board, int x, int y, int m, int pipefd);
int parent_process();

int main (int argc, char** argv) {
	//Get the inputs from command line
	//Check if there are enough arguments on the commandline
	if (argc != 3) {
		fprintf(stderr, "ERROR: Incorrect argument(s)\n");
		fprintf(stderr, "USAGE: hw2.out <m> <n>");
		return EXIT_FAILURE;
	}
	//Get the arguments from the commandline, check if they are greater than zero
	int m = atoi(*(argv+1));
	int n = atoi(*(argv+2));
	if (m < 1 || n < 1) {
		fprintf(stderr, "ERROR: Arguments must be at least 1\n");
		fprintf(stderr, "USAGE: hw2.out <m> <n>, m >= 1 && n >= 1");
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
		return EXIT_FAILURE;
	}
	// Create an empty board in the parent process, it will be copied to the children
	char** board = calloc(m, sizeof(char*));
	for (int i = 0; i < m; i = i + 1) {
		*(board+i) = calloc(n, sizeof(char));
	}
	//Format printing for parent process, then create children process
	printf("P%d:  solving the Abridged (m,n)-Queens problem for %dx%d board\n", getpid(), m, n);
	pid_t* pids = calloc(n, sizeof(pid_t));		//Calloc for the og children, which is n
	int curRow = 0;
	if (pids == NULL) {
		fprintf(stderr, "ERROR: fork() failed\n");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < n; i++) {
		pid_t childPID = fork();
		if (childPID == -1) {
			fprintf(stderr, "ERROR: fork() failed\n");
			return EXIT_FAILURE;
		}
		if (childPID == 0) {
			free(pids);
			return placeQueen(board, curRow, i, m, *(pipefd+1));
		}
		*(pids+i) = childPID;
	}
	parent_process(n, pids);
	return EXIT_SUCCESS;
}

int placeQueen(char** board, int x, int y, int m, int pipefd) {
	//Place no matter what
	*(*(board+x)+y) = 'Q';
	//Check how many child can be forked
	int nChild = 0;
	for (int v = 0; v < y; v = v + 1) {
		//Check if the y coordinate is okay
		if (!(v == y-1 || v == y || v+1 == y)) {
			//Check the column
			int qCount = 0;
			for (int k = 0; k < x; k = k + 1) {
				if (*(*(board+k)+v) == 'Q') {
					qCount = qCount + 1;
				}
			}
			if (qCount == 0) {
				nChild = nChild + 1;
			}
		}
	}
	if (nChild == 0) {
		//Termination state, write to pipe
		printf("P%d, dead end at row#%d; notifying top-level parent\n", getpid(), x+1);
		//Formatting our integer result to string before writing
		return EXIT_SUCCESS;
	}
	else {
		//fork the children
		printf("P%d: %d possible moves at row #%d; creating %d child processes...\n", getpid(), nChild, x+1, nChild);
		pid_t* pids = calloc(nChild, sizeof(pid_t));
		
	}

	return EXIT_SUCCESS;
}

int parent_process() {
	return EXIT_SUCCESS;
}


for (int x = 0; x < m; x = x + 1) {
		int nChild = 0;
		//At each row, see if each position is a valid placement
		//Keep track of the number of children process we need to fork
		for (int y = 0; y < n; y = y + 1) {
			int vPlace = validPlace(board, x, y, n);
			if (vPlace != -1) {
				nChild = nChild + 1;
			}
		}
		if (nChild == 0) {
			return EXIT_SUCCESS;
		}
		//Try to find all the 
		int* yCoors = calloc(nChild, sizeof(int));
		int yIdx = 0;
		for (int y = 0; y < n; y = y + 1) {
			int vPlace = validPlace(board, x, y, n);
			if (vPlace != -1) {
				*(yCoors+yIdx) = vPlace;
				yIdx = yIdx + 1;
			}
		}
		yIdx = 0;
		//Create child processes
		printf("P%d: %d possible moves at row #%d; creating %d child processes...", getpid(), nChild, x, nChild);
		pid_t* pids = calloc(nChild, sizeof(pid_t));
		if(pids == NULL) {
			fprintf(stderr, "ERROR: fork() failed\n");
			return EXIT_FAILURE;
		}
		for (int i = 0; i < nChild; i = i + 1) {
			pid_t p = fork();
			if(p == -1) {
				fprintf(stderr, "ERROR: fork() failed\n");
				return EXIT_FAILURE;
			}
			if (p == 0) {
				free(pids);
				return placeQueen(board, x, *(yCoors+yIdx));
				yIdx = yIdx + 1;
			}
			*(pids+i) = p;
		}
		free(yCoors);
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
					if (WIFSIGNALED(status)) {
						abort();
					}
					else if (WIFEXITED(cp)) {
						free(pids);
						for (int i = 0; i < row; i = i + 1) {
							free(*(board+i));
						}
						free(board);
						free(pipefd);
						return EXIT_SUCCESS;
					}
				#endif
				waitpid(cp, &status, 0);
				if (WIFSIGNALED(status)) {
					abort();
				}
				else if (WIFEXITED(cp)) {
					free(pids);
					for (int i = 0; i < row; i = i + 1) {
						free(*(board+i));
					}
					free(board);
					free(pipefd);
					return EXIT_SUCCESS;
				}
				*(pids + counter) = cp;
				counter = counter + 1;
			}
		}
		return EXIT_SUCCESS;
	} else {
		if (x == row-1) {
			char* nQ = calloc(3, sizeof(char));
			sprintf(nQ,"%d",x+1);
			write(*(pipefd+1), nQ ,strlen(nQ));
			free(nQ);
			#ifndef QUIET
				printf("P%d: found a solution; notifying top-level parent\n", getpid());
			#endif 
		}
		else {
			char* nQ = calloc(3, sizeof(char));
			sprintf(nQ,"%d",x+1);
			write(*(pipefd+1), nQ ,strlen(nQ));
			free(nQ);
			#ifndef QUIET
				printf("P%d: dead end at row #%d; notifying top-level parent\n", getpid(), x+1);
			#endif
		}
		close(*(pipefd+1));
		for (int i = 0; i < row; i = i + 1) {
			free(*(board+i));
		}
		free(board);
		free(pipefd);
		return EXIT_SUCCESS;
	}
	//Managing return values of child processes
	//printf("Wait for my children to be done\n");
}