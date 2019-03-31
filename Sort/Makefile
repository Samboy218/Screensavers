modName = sort
installpath = /usr/lib/xscreensaver/

all: $(modName)
    
$(modName): sort.cpp bogoSort.h combSort.h mergeSort.h radixSort.h sorter.h bitonicSort.h cocktailSort.h heapSort.h quickSort.h shellSort.h vroot.h bubbleSort.cpp sort.cpp sorter.cpp sortManager.cpp
	g++ -Wall -c *.cpp
	g++ -O2 -s -DNDEBUG -o $(modName) *.o -L/usr/lib/x86_64-linux-gnu -lX11 --std=c++11

.PHONY: debug
debug: $(sourceFiles)
	g++ -c *.cpp -ggdb
	g++ -o $(modName) *.o -L/usr/lib/x86_64-linux-gnu -lX11 --std=c++11 -ggdb

.PHONY: speed_debug
speed_debug: $(sourceFiles)
	g++ -c *.cpp -pg -no-pie
	g++ -o $(modName) *.o -L/usr/lib/x86_64-linux-gnu -lX11 --std=c++11 -pg -no-pie

.PHONY: clean
clean:
	rm -f $(modName)
	rm -f *.o

.PHONY: install
install: $(modName)
	sudo cp $(modName) $(installpath)

.PHONY: uninstall
uninstall: 
	sudo rm -f $(installpath)$(modName)

