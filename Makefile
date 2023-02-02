# Executables to build using 'make all'
EXECUTABLES = bin/shell

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
		touch src/main.c src/hierarchy.c src/history.c src/parser.c src/pipe.c
clean:
		rm -f $(EXECUTABLES) $(OBJS)

# Create project
bin/shell: $(OBJS)
		$(CC) -o bin/shell $(OBJS)
main.o: src/main.c
		$(CC) $(CFLAGS) src/main.c
hierarchy.o: src/hierarchy.c lib/hierarchy.h lib/path.h
		$(CC) $(CFLAGS) src/hierarchy.c
history.o: src/history.c lib/history.h
		$(CC) $(CFLAGS) src/history.c
parser.o: src/parser.c lib/parser.h
		$(CC) $(CFLAGS) src/parser.c
pipe.o: src/pipe.c lib/pipe.h lib/path.h
		$(CC) $(CFLAGS) src/pipe.c
