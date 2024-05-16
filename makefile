mst: main.o graph.o algorithm.o
	gcc main.o graph.o algorithm.o -o mst

main.o: main.c graph.h algorithm.h
	gcc -c main.c

graph.o: graph.c graph.h
	gcc -c graph.c

algorithm.o: algorithm.c algorithm.h graph.h
	gcc -c algorithm.c
