#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#if 0
1st input val = cache size
2nd input val = file to read
#endif

int hash(char* toHash, int cacheSize) {
	int hashVal = 0;
	for (int x = 0; x < strlen(toHash); x = x+1) {
		hashVal = hashVal + *(toHash+x);
	}
	return hashVal%cacheSize;
}

int main(int argc, char** argv) {
	#if 0
		first check if there are enough/ correct input argument
	#endif
	if (argc < 3) {
		fprintf(stderr, "ERROR: Invalid number of input arguments.\n");
		return EXIT_FAILURE;
	}
	if (atoi(*(argv+1)) == 0 || atoi(*(argv+1)) < 0) {
		fprintf(stderr, "ERROR: First argument is not valid, must be an integer at least 1.\n");
		return EXIT_FAILURE;
	}
	int cacheSize = atoi(*(argv+1));

	#if 0
			Setup the cache, pointers are 8 bytes each, multiply input by size of char*
	#endif
	char** workCache = calloc(cacheSize, sizeof(char*));

	int current = 2;
	while (current < argc) {
		char* curFile = *(argv+current);
		#if 0
			try opening the file, check to see if file properly opens
		#endif
		int fd = open(curFile, O_RDONLY);
		if (fd == -1) {
			perror("Error: File failes to open, check if file exists or spelling of input filename.");
			return EXIT_FAILURE;
		}
		int totalChars = lseek(fd, 0, SEEK_END);
		//printf("totalChars: %d\n", totalChars);
		lseek(fd, 0, SEEK_SET);
		char* bigBuff = calloc(totalChars+1, sizeof(char*));
		//Read the entire file in
		read(fd, bigBuff, totalChars);
		*(bigBuff+totalChars) = 0;
		//printf("%s\n", bigBuff);
		//Now we are going to parse through the string we read in
		int wordLen = 0;
		lseek(fd, 0, SEEK_SET);
		for (int n = 0; n < totalChars+1; n = n + 1) {
			int alnumRes = isalnum(*(bigBuff+n));
			//printf("alnum(%c): %d\n", *(bigBuff+n), alnumRes);
			if (alnumRes != 0) {
				wordLen++;
			}
			else {
				if (wordLen >= 3) {
					lseek(fd, n-wordLen, SEEK_CUR);
					char* word = calloc(wordLen+1, sizeof(char*));
					read(fd, word, wordLen);
					*(word+wordLen) = 0;
					//Hash them here
					int hashRes = hash(word, cacheSize);
					//Go to see if the cache was already occupied
					if (*(workCache+hashRes) == NULL) {
						//Position unoccupied, just slot the new word in by allocating enough space and strcpy()
						*(workCache+hashRes) = calloc(wordLen+1, sizeof(char));
						strcpy(*(workCache+hashRes), word);
						printf("Word %c%s%c ==> %d (calloc)\n", 34, *(workCache+hashRes), 34, hashRes);
					} 
					else {
						if (strlen(*(workCache+hashRes)) == strlen(word)) {
							strcpy(*(workCache+hashRes), word);
							printf("Word %c%s%c ==> %d (nop)\n", 34, *(workCache+hashRes), 34, hashRes);
						}
						else {
								//Free the block first and realloc enough space
							*(workCache+hashRes) = realloc(*(workCache+hashRes), wordLen+1);
							strcpy(*(workCache+hashRes), word);
							printf("Word %c%s%c ==> %d (realloc)\n", 34, *(workCache+hashRes), 34, hashRes);
						}
					}
					free(word);			//Free the word
				}
				wordLen = 0;
				lseek(fd, 0, SEEK_SET);
			}
		}
		free(bigBuff);
		close(fd);
		current = current + 1;
	}
	//Awesome, everything is done, let's format the output!
	printf("\nCache:\n");
	for (int f = 0; f < cacheSize; f++) {
		if (*(workCache+f) != NULL) {
			printf("%c%d%c ==> %c%s%c\n", 91, f, 93, 34, *(workCache+f), 34);
		}
	}

	for (int v = 0; v < cacheSize; v = v+1) {
		free(*(workCache+v));
	}
	free(workCache);
	return EXIT_SUCCESS;

}