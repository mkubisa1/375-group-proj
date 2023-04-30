all: main

main: main.o
	g++ main.o -o main

main.o: main.cpp edge.h 
	g++ -c main.cpp edge.h
# .h files would go here as well

clean:
	rm -f *.o main a.out *.gch *.log