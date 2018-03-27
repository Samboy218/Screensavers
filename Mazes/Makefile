installpath = /usr/lib/xscreensaver

all: mymaze

mymaze: main.o maze.o mazeNode.o nodeStack.o mazeSolver.o
	g++ -o mymaze main.o maze.o mazeNode.o nodeStack.o mazeSolver.o -L/usr/lib/x86_64-linux-gnu -lX11

main.o: main.cpp
	g++ -c -o main.o main.cpp

maze.o: maze.cpp maze.h mazeNode.o nodeStack.o
	g++ -c -o maze.o maze.cpp

mazeNode.o: mazeNode.cpp mazeNode.h
	g++ -c -o mazeNode.o mazeNode.cpp

nodeStack.o: nodeStack.cpp nodeStack.h
	g++ -c -o nodeStack.o nodeStack.cpp

mazeSolver.o: maze.o mazeSolver.h mazeSolver.cpp
	g++ -c -o mazeSolver.o mazeSolver.cpp

.PHONY: debug
debug: *.cpp *.h
	g++ -c -o nodeStack.o nodeStack.cpp -g -g -lefence
	g++ -c -o mazeNode.o mazeNode.cpp -g -lefence
	g++ -c -o maze.o maze.cpp -g -lefence
	g++ -c -o main.o main.cpp -g -lefence
	g++ -c -o mazeSolver.o mazeSolver.cpp -g -lefence
	g++ -o mymaze main.o maze.o mazeNode.o nodeStack.o mazeSolver.o -g -lefence -L/usr/lib/x86_64-linux-gnu -lX11
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf mymaze
.PHONY: install
install: mymaze
	cp mymaze $(installpath)
