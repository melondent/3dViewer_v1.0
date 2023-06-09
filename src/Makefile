APP = build/3DViewer_v1.app
CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
CHECK_FLAGS = -lcheck
FUNC = parser.c rotation.c move.c

all: install test clean

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: uninstall build
	@mkdir $(HOME)/Desktop/3DViewer_v1
	@cp -rf $(APP) $(HOME)/Desktop/3DViewer_v1
	make clean

uninstall: clean
	@rm -rf $(HOME)/Desktop/3DViewer_v1

dvi:
	open info.html

dist:
	rm -rf Archive_3DViewer_v1/
	mkdir Archive_3DViewer_v1/
	mkdir Archive_3DViewer_v1/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user Archive_3DViewer_v1/src/
	tar cvzf Archive_3DViewer_v1.tgz Archive_3DViewer_v1/
	mv Archive_3DViewer_v1.tgz $(HOME)/Desktop/
	rm -rf Archive_3DViewer_v1/

test:
	checkmk clean_mode=1 test.check > test.c
	gcc -Wall -Werror -Wextra $(FUNC) test.c -lcheck
	rm test.c
	./a.out

gcov_report:
	rm -f *.g*
	checkmk clean_mode=1 test.check > test.c
	gcc -Wall -Werror -Wextra $(FUNC) test.c -lcheck --coverage
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	rm test.c
	open report/index.html
	rm -rf *.gcda *.gcno *.info

3DViewer_v1.o:
	$(CC+FLAGS) -c *.c

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf test report
	rm -rf test.c
	rm -rf ./build*
	rm -rf a.out

rebuild: clean uninstall all

reinstall: clean uninstall install