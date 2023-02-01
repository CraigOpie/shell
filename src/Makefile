# Executables to build using 'make all'
EXECUTABLES = ../bin/shell

# The default compiler
CC = g++

# The FLAGS variables sets compile flags for the CC
CFLAGS = -v -c -ansi -pedantic-errors -Wall

# The object files to be linked
OBJS = main.o hierarchy.o history.o parser.o pipe.o

# Make commands
all: $(EXECUTABLES)

# Alter the existing files
ready:
		touch main.c hierarchy.c history.c parser.c pipe.c
clean:
		rm -f $(EXECUTABLES) $(OBJS)

# Create project
../bin/shell: $(OBJS)
		$(CC) -o ../bin/shell $(OBJS)
main.o: main.c
		$(CC) $(CFLAGS) main.c
hierarchy.o: hierarchy.c hierarchy.h path.h
		$(CC) $(CFLAGS) hierarchy.c
history.o: history.c history.h
		$(CC) $(CFLAGS) history.c
parser.o: parser.c parser.h
		$(CC) $(CFLAGS) parser.c
pipe.o: pipe.c pipe.h path.h
		$(CC) $(CFLAGS) pipe.c
