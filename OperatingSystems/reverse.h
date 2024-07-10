#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>

char * reverse( char * s )
{
	#if 0
		We prefer malloc over calloc because calloc initialized each space.
		The input string could be much shorter. Using calloc can pre-occupy space
		that is not going to be needed. 

		Find the length of the string
	#endif
	int length = strlen(s);
	char* buffer = malloc(length);
	#if 0
		We reverse the string that is placed into buffer
	#endif
	for (char* itr = s; *itr; itr++) {
		*(buffer+length-1) = *itr;
		length--;
	}
	#if 0
		Reassigning the values to the input given
		We know the value at the same position should be assigned, 
		we can just use a normal for loop since the value added to both pointers will be the same

	#endif
	length = strlen(s);
	for (int n = 0; n < length;n++) {
		*(s+n) = *(buffer+n);
	}
	#if 0
		Free the buffer allocated
	#endif
	free(buffer);
	return s;
	#if 0 
		I tried, but I was not able to write a solution that compiles and runs without error on first try
	#endif
}
