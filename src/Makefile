.PHONY: all clean check tests gcov_report dvi install uninstall dist
CC = gcc
CFLAGS =-Wall -Wextra -Werror -pedantic -std=c11
CFLAGS_TEST =`pkg-config --cflags --libs check`
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
ALL_SOURCES_C = smartcalc1.c tests.c
ALL_SOURCES_H = smartcalc1.h
OUTFILE_TEST = tests

all: prepare
	make -f qMakefile

install: all
	@test -d bin || mkdir -p bin
	rm -f -r bin/smartcalc1.app
	/usr/local/bin/qmake -install qinstall smartcalc1.app bin/smartcalc1.app
	-strip bin/smartcalc1.app/Contents/MacOS/smartcalc1

uninstall: prepare
	-rm -f -r bin/smartcalc1.app
	-rmdir bin/

clean: prepare
	@-rm *.gcov *.gcda *.gcno *.info *.xml *.gz 2>/dev/null
	@-rm tests 2>/dev/null
	@-rm -rf lcov_report bin report 2>/dev/null
	@make -f qMakefile clean
	@-rm -rf smartcalc1.app
	@-rm qMakefile

dvi:
	# brew install doxygen
	cd doc && doxygen doxygen.conf

dist:
	tar -czpf smartcalc1.tar.gz *.cpp *.h *.ui Makefile smartcalc1.pro smartcalc1.pro.user

tests:
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	./tests

gcov_report:
	@$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(ALL_SOURCES_C) -o $(OUTFILE_TEST)
	./tests
	lcov --no-external -c -d . -o tests.info
	genhtml tests.info -o report
	open ./report/index.html

prepare:
	qmake -o qMakefile

checkall: style check leaks

style:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(ALL_SOURCES_C) $(ALL_SOURCES_H)

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(ALL_SOURCES_C) $(ALL_SOURCES_H)

leaks: tests
	CK_FORK=no leaks --atExit -- ./tests

brew:
    # cd ~/goinfre
    # git clone https://github.com/Homebrew/brew homebrew
    # eval "$(~/goinfre/homebrew/bin/brew shellenv)"
    # brew install lcov
