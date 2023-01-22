# Executables to build using 'make all'
EXECUTABLES = shell_project

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
		touch main.cpp hierarchy.cpp history.cpp parser.cpp pipe.cpp
clean:
		rm -f $(EXECUTABLES) $(OBJS)

# Create project
shell_project: $(OBJS)
		$(CC) -o shell_project $(OBJS)
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp
hierarchy.o: hierarchy.cpp hierarchy.h path.h
		$(CC) $(CFLAGS) hierarchy.cpp
history.o: history.cpp history.h
		$(CC) $(CFLAGS) history.cpp
parser.o: parser.cpp parser.h
		$(CC) $(CFLAGS) parser.cpp
pipe.o: pipe.cpp pipe.h path.h
		$(CC) $(CFLAGS) pipe.cpp
