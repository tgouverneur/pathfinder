CC = g++

.SILENT:

all:	pathfinder.o	main

pathfinder.o:	pathfinder.cpp	pathfinder.h
	$(CC)	-c pathfinder.cpp
	echo "pathfinder.o compiled"

main:	pathfinder.o 	pathfinder.h	main.cpp
	$(CC)	main.cpp pathfinder.o -o main
	echo "main.cpp compiled and linked"

clean:	
	rm *.o main
