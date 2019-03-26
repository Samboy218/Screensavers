installpath = /usr/lib/xscreensaver

all: mymaze

mymaze: main.o maze.o mazeNode.o nodeStack.o nodeQueue.o mazeSolver.o mazeSolverDFS.o mazeSolverBFS.o mazeSolverA.o
	g++ -o mymaze main.o maze.o mazeNode.o nodeStack.o nodeQueue.o mazeSolver.o mazeSolverDFS.o mazeSolverBFS.o mazeSolverA.o -L/usr/lib/x86_64-linux-gnu -lX11

main.o: main.cpp
	g++ -c -o main.o main.cpp

maze.o: maze.cpp maze.h mazeNode.o nodeStack.o
	g++ -c -o maze.o maze.cpp

mazeNode.o: mazeNode.cpp mazeNode.h
	g++ -c -o mazeNode.o mazeNode.cpp

nodeStack.o: nodeStack.cpp nodeStack.h
	g++ -c -o nodeStack.o nodeStack.cpp

nodeQueue.o: nodeQueue.cpp nodeQueue.h
	g++ -c -o nodeQueue.o nodeQueue.cpp

mazeSolver.o: maze.o mazeSolver.h mazeSolver.cpp
	g++ -c -o mazeSolver.o mazeSolver.cpp

mazeSolverDFS.o: maze.o mazeSolver.o mazeSolverDFS.h mazeSolverDFS.cpp
	g++ -c -o mazeSolverDFS.o mazeSolverDFS.cpp

mazeSolverBFS.o: maze.o mazeSolver.o mazeSolverBFS.h mazeSolverBFS.cpp
	g++ -c -o mazeSolverBFS.o mazeSolverBFS.cpp

mazeSolverA.o: maze.o mazeSolver.o nodeStack.o mazeSolverA.h mazeSolverA.cpp
	g++ -c -o mazeSolverA.o mazeSolverA.cpp

.PHONY: debug
debug: *.cpp *.h
	g++ -c -o nodeStack.o nodeStack.cpp -g -g -lefence
	g++ -c -o nodeQueue.o nodeQueue.cpp -g -g -lefence
	g++ -c -o mazeNode.o mazeNode.cpp -g -lefence
	g++ -c -o maze.o maze.cpp -g -lefence
	g++ -c -o main.o main.cpp -g -lefence
	g++ -c -o mazeSolver.o mazeSolver.cpp -g -lefence
	g++ -c -o mazeSolverA.o mazeSolverA.cpp -g -lefence
	g++ -c -o mazeSolverDFS.o mazeSolverDFS.cpp -g -lefence
	g++ -c -o mazeSolverBFS.o mazeSolverBFS.cpp -g -lefence
	g++ -o mymaze main.o maze.o mazeNode.o nodeStack.o nodeQueue.o mazeSolver.o mazeSolverA.o mazeSolverDFS.o mazeSolverBFS.o -g -lefence -L/usr/lib/x86_64-linux-gnu -lX11

.PHONY: speed_debug
speed_debug: *.cpp *.h
	g++ -c -o nodeStack.o nodeStack.cpp -pg -no-pie
	g++ -c -o nodeQueue.o nodeQueue.cpp -pg -no-pie
	g++ -c -o mazeNode.o mazeNode.cpp -pg -no-pie
	g++ -c -o maze.o maze.cpp -pg -no-pie
	g++ -c -o main.o main.cpp -pg -no-pie
	g++ -c -o mazeSolver.o mazeSolver.cpp -pg -no-pie
	g++ -c -o mazeSolverA.o mazeSolverA.cpp -pg -no-pie
	g++ -c -o mazeSolverDFS.o mazeSolverDFS.cpp -pg -no-pie
	g++ -c -o mazeSolverBFS.o mazeSolverBFS.cpp -pg -no-pie
	g++ -o mymaze main.o maze.o mazeNode.o nodeStack.o nodeQueue.o mazeSolver.o mazeSolverA.o mazeSolverDFS.o mazeSolverBFS.o -pg -no-pie -L/usr/lib/x86_64-linux-gnu -lX11

.PHONY:clean
clean:
	rm -rf *.o
	rm -rf mymaze

.PHONY: install
install: mymaze
	cp mymaze $(installpath)
