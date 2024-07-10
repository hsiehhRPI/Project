#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "reverse.h"

int main(int agrc, char** argv) {
	char * sample = malloc(17);
	strcpy(sample,"abcdefghijklmnop");
	char* result = reverse(sample);
	printf("%s\n", result);
	free(sample);
	return EXIT_SUCCESS;
}