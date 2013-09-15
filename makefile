COMP=g++ -std=c++0x
EXE=cubesolved
FLAGS=-Wall -g

all: cube.o tester.o
	$(COMP) $(FLAGS) cube.o tester.o -o $(EXE)

cube.o: cube.cpp cube.h
	$(COMP) $(FLAGS) -c cube.cpp cube.h

tester.o: tester.cpp
	$(COMP) $(FLAGS) -c tester.cpp

clean:
	rm -rf *.o *.gch $(EXE)

