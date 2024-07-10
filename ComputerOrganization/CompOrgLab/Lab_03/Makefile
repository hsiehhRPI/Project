OBJFILES = *c
PROGRAM = matrixops
CC = gcc
CFLAGS = -Wall -Wextra 

all: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ -I include

clean: 
	rm all 
	
.PHONY: all clean