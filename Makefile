all: main

main: main.o MIR.o
	g++ MIR.o main.o -o MIR

main.o: main.cpp
	g++ -c main.cpp

MIR.o: MIR.cpp
	g++ -c MIR.cpp

clean:
	rm -rf *.o MIR
