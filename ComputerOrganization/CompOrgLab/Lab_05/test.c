#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main() {
	char cmd[40];	//Input string, all commands in one line
	char parsed[10][20];	//Parse the inputs into specific commands
	
		printf("Please enter your command");
		fgets(cmd, 256, stdin);
		printf(cmd);
		exit(0);
}