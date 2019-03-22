modName = growth
sourceName = $(modName).cpp
installpath = /usr/lib/xscreensaver/


all: $(modName)
    
$(modName): $(sourceName) vroot.h
	 g++ -O2 -s -DNDEBUG -o $(modName) $(sourceName) -L/usr/lib/x86_64-linux-gnu -lX11

.PHONY: super
super: $(sourceName) vroot.h
	 g++ -O3 -s -DNDEBUG -o $(modName) $(sourceName) -L/usr/lib/x86_64-linux-gnu -lX11

.PHONY: clean
clean:
	rm -f $(modName)

.PHONY: install
install: $(modName)
	cp $(modName) $(installpath)

.PHONY: uninstall
uninstall: 
	rm -f $(installpath)$(modName)

.PHONY: debug
debug: $(sourceName) vroot.h
	 g++ -o $(modName) $(sourceName) -L/usr/lib/x86_64-linux-gnu -lX11 -pg
