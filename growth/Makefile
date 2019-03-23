modName = growth
souceFiles = board.cpp cell.cpp faction.cpp growth.cpp move.cpp board.h cell.h faction.h move.h vroot.h
installpath = /usr/lib/xscreensaver/


all: $(modName)
    
$(modName): $(sourceFiles)
	g++ -c *.cpp
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
	cp $(modName) $(installpath)

.PHONY: uninstall
uninstall: 
	rm -f $(installpath)$(modName)

