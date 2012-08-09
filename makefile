VPATH = src:headers:tests

.PHONY: all
all: FileStalker FileStalkerUI

FileStalker: DirectoryMonitor.o File.o List.o HashMap.o
	g++ -o FileStalker "installer/FileStalkerLocal.cpp" "src/DirectoryMonitor.cpp" "src/File.cpp"

FileStalkerI: DirectoryMonitor.o File.o List.o HashMap.o
	g++ -o FileStalker "installer/FileStalkerInstall.cpp" "src/DirectoryMonitor.cpp" "src/File.cpp"

FileStalkerUI: UI.cpp Parser.cpp
	g++ src/UI.cpp src/Parser.cpp installer/FileStalkerUILocal.cpp -o FileStalkerUI

FileStalkerUII: UI.cpp Parser.cpp
	g++ src/UI.cpp src/Parser.cpp installer/FileStalkerUIInstall.cpp -o FileStalkerUI

Valgrind: FileStalker FileStalkerUI
	g++ -o FileStalker -g -O0 "installer/FileStalkerLocal.cpp" "src/DirectoryMonitor.cpp" "src/File.cpp"
	g++ -O0 -g installer/FileStalkerUILocal.cpp src/UI.cpp src/Parser.cpp -o FileStalkerUI

DirectoryMonitor.o: DirectoryMonitor.cpp File.o
	g++ -o DirectoryMonitor.o -c "src/DirectoryMonitor.cpp"
File.o: File.cpp
	g++ -o File.o -c "src/File.cpp"
HashMap.o: HashMap.h
	g++ -o HashMap.o -c "headers/HashMap.h"
List.o: List.h
	g++ -o List.o -c "headers/List.h"
UI.o: UI.cpp
	g++ -o UI.o -c "src/UI.cpp"

.PHONY: install
install: FileStalkerI FileStalkerUII
	-rm /var/log/filestalker.log
	touch /var/log/filestalker.log
	chmod 666 /var/log/filestalker.log
	cp FileStalker /usr/bin/filestalker
	cp FileStalkerUI /usr/bin/filestalkerui
	-rm FileStalker FileStalkerUI
.PHONY: uninstall
uninstall:
	-rm /var/log/filestalker.log
	-rm /usr/bin/filestalker
	-rm /usr/bin/filestalkerui

.PHONY: clean
clean:
	find . -depth -name '*.o' -exec rm -f '{}' \;
	find . -depth -name '*~' -exec rm -f '{}' \;

.PHONY: clear
clear: clean
	-rm FileStalker FileStalkerUI
