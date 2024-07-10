#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
int main (int agrc, char* argv) {
	if (argc < 2) {
		printf("Invalid input\n");
	}
	printf("%s\n", argv[1]);
}