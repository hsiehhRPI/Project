#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

int main() {
	char cmd[60];	//Input string, all commands in one line
	char heap[10][60];		//Store already executed commands
	int heapSize = 0;		//To keep track how many elements are in an array currently
	while (strstr(cmd,"exit")==NULL) {
		printf(">mockShell$ ");
		fgets(cmd, 60, stdin);
		strtok(cmd, "\n");
		if (strstr(cmd,"time") != NULL) {
			struct tm* ptr;
			time_t curTime;
			curTime = time(NULL);
			ptr = localtime(&curTime);
			printf("Current time: %s\n", asctime(ptr));
			strcpy(heap[heapSize], cmd);
			heapSize++;
			cmd[0] = '\0';
		}
		else if (strstr(cmd,"date") != NULL) {
			time_t curTime = time(NULL);
			struct tm date = *localtime(&curTime);
			printf("Today's date: %d/%02d/%02d\n", date.tm_year+1900, date.tm_mon+1, date.tm_mday);
			strcpy(heap[heapSize], cmd);
			heapSize++;
			cmd[0] = '\0';
		}
		else if (strstr(cmd,"history") != NULL) {
			strcpy(heap[heapSize], cmd);
			heapSize++;
			for (int n = 0; n < heapSize; n++) {
				printf("%s", heap[n]);
				printf("\n");
			}
			cmd[0] = '\0';
		}
		else if (strstr(cmd,"echo") != NULL) {
			strcpy(heap[heapSize], cmd);
			heapSize++;
			int cmdSZ = strlen(cmd);
			if (strcmp(cmd,"echo")!=0) {
				for (int n = 5; n < cmdSZ; n++) {
					printf("%c", cmd[n]);
				}
				printf("\n");
			}
			//printf("%s", heap[heapSize-1]);
			cmd[0] = '\0';
		} 
		else if (strstr(cmd,"exit") != NULL) {
			exit(0);
		}
		else {
			strcpy(heap[heapSize], cmd);
			heapSize++;
			char* arg[10];
			char* sub = strtok(cmd, " ");
			arg[0] = sub;
			int v = 1;
			while (sub != NULL) {
				sub = strtok(NULL, " ");
				if (v > 9) {
					arg[v] = sub;
					v++;
				}
			}
			arg[v] = NULL;
			if (fork()) {
				wait(NULL);
			}
			else {
				if (strlen(arg[0]) > 0 && arg[0][0] != '.') {
					char* tmp = (char *) malloc((strlen(arg[0])+7)*sizeof (char));
					strcpy(tmp, "/bin/");
					strcat(tmp, arg[0]);
					arg[0] = (char *) malloc((strlen(tmp)+1)*sizeof (char)); 
					strcpy(arg[0], tmp);					
				}
				if (execv(arg[0], arg)==-1) {
					printf("Couldn't run command, try again.\n");
				}

				exit(0);
			}
		}
	}
	exit(0);
}