#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char** argv) {
	//Have the fileName ready
	char* fileName = *(argv+1);
	//Forking processes
	pid_t p = fork();
	if (p == -1) {
		fprintf(stderr, "PARENT: fork() failed\n");
		return 1;
	}
	if (p == 0) {	//Child process, have that child also fork a process
		pid_t gcp = fork();
		if (gcp == -1) {
			fprintf(stderr, "CHILD: fork() failed\n");
			return -1;
		}
		if (gcp == 0) {
			//Try reading the file here
			int fd = open(fileName, O_RDONLY);
			if (fd == -1) {
				fprintf(stderr, "GRANDCHILD: open() failed: No such file or directory\n");
				return -1;
			}
			//File is fine, find file size to see how much memory should be allocated
			int totalSize = lseek(fd, 0, SEEK_END);
			lseek(fd,0,SEEK_SET);	//Reset read location to the start of the file
			char* fBuf = calloc(totalSize+1, sizeof(char*));
			read(fd, fBuf, totalSize);
			*(fBuf+totalSize) = 0;
			//We can start counting now
			int pairCount = 0;
			int lBrackCount = 0;
			for (int n = 0; n < strlen(fBuf); n++) {
				if (*(fBuf+n) == '(') {
					lBrackCount = lBrackCount + 1;
				}
				else if (*(fBuf+n) == ')' && lBrackCount > 0) {
					pairCount = pairCount + 1;
					lBrackCount = lBrackCount - 1;
				}
			}
			free(fBuf);
			close(fd);
			//Awesome, we finished counting
			if (pairCount > 127) {	
			//We know return -1 will actually give 255 when we use WEXITSTATUS(gcStatus)
			//We need to prevent any doubling == 255
			//Meaning the largest pairs we accounted for should be 254 after doubling
			//So the max cap for granchild process should actually be 127, so the next doubling would not have error
				fprintf(stderr, "GRANDCHILD: more valid parentheses than return value can handle.\n");
				return -1;
			}
			else if (pairCount == 1) {
				printf("GRANDCHILD: counted %d properly nested pair of parentheses\n", pairCount);
			}
			else {
				printf("GRANDCHILD: counted %d properly nested pairs of parentheses\n", pairCount);
			}
			return pairCount;
		}
		else {
			//Child process here
			int gcStatus;
			waitpid(gcp, &gcStatus, 0);
			if (WIFSIGNALED(gcStatus)) {
				fprintf(stderr ,"CHILD: rcvd -1 (error)\n");
				return -1;
			}
			else if (WIFEXITED(gcStatus)) {
				int result = WEXITSTATUS(gcStatus);
				if (result == 255) {
					fprintf(stderr ,"CHILD: rcvd -1 (error)\n");
					return -1;
				}
				printf("CHILD: doubled %d; returning %d\n", result, 2*result);
				return 2*result;
			}
		}
	}
	else {
		//Parent process here
		int cStatus;
		waitpid(p, &cStatus, 0);			
		if (WIFSIGNALED(cStatus)) {
			fprintf(stderr, "PARENT: rcvd -1 (error)\n");
			return EXIT_FAILURE;
		}
		else if (WIFEXITED(cStatus)) {
			int result = WEXITSTATUS(cStatus);
			if (result == 255) {
				fprintf(stderr, "PARENT: rcvd -1 (error)\n");
				return EXIT_FAILURE;
			}
			printf("PARENT: there are %d properly nested parentheses\n", result);
		}
	}
	return EXIT_SUCCESS;
}