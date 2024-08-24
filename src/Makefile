CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
SOURCES = $(wildcard s21_*.cc) 
OBJECTS = $(SOURCES:.cc=.o)
TESTS = $(wildcard tests/test_*.cc)
OBJECTS_TESTS = $(TESTS:.cc=.o)
PROJECT = SmartCalc
EXECUTABLE = test
OS = $(shell uname)
REPORT = report
INSTALL_DIR = build
ccFiles = $(shell find . -name "*.cc")
headFiles = $(shell find . -name "*.h")

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	LIBFLAGS = $(shell pkg-config --cflags --libs gtest) -lgtest_main
endif
ifeq ($(OS), Darwin)
	OPEN_CMD = open
	LIBFLAGS = -lgtest -lgmock -pthread
endif

#all, install, uninstall, clean, dvi, dist, testsы

all: clean clang-format $(PROJECT).a test install

install: clean
	mkdir $(INSTALL_DIR)
	cd $(INSTALL_DIR) && qmake ../SmartCalc && make

uninstall:
	rm -rf $(INSTALL_DIR)

clean: 
	rm -rf $(EXECUTABLE) $(PROJECT).a $(PROJECT)_test.a *.gcda *.gcno *.info
	rm -rf $(REPORT)

dvi:
	$(OPEN_CMD) ../README.md

dist: install uninstall
	rm -rf dist-molliekh-smartcalc.tar.gz
	tar -czf dist-molliekh-smartcalc.tar.gz *

tests: clang-format $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -L. $(PROJECT).a $(LIBFLAGS) -o $(EXECUTABLE)
	clear
	./$(EXECUTABLE)

run: $(INSTALL_DIR)/$(PROJECT)
	$(OPEN_CMD) $^

gcov_report: clean clang-format $(SOURCES) $(PROJECT)_test.a
	$(CC) $(CFLAGS) $(SOURCES) --coverage -L. $(PROJECT)_test.a $(LIBFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov --no-external -t "$(PROJECT)" -o $(PROJECT).info -c -d . 
	genhtml -o $(REPORT) $(PROJECT).info
	$(OPEN_CMD) $(REPORT)/index.html

$(PROJECT).a:$(OBJECTS)
	ar -rcs $@ $^
	ranlib $@
	rm -f $^

$(PROJECT)_test.a:$(OBJECTS_TESTS)
	ar -rcs $@ $^
	ranlib $@
	rm -f $^

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clang-format: $(ccFiles) $(headFiles)
	@echo "\033[33m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m"
	@echo "\033[33m┃   Checking your code for Google Style   ┃\033[0m"
	@echo "\033[33m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m"
	clang-format -i $^
	clang-format -style=Google -n $^

rebuild:
	clean | make

cc: *.cc $(TESTS)
	cccheck -I $(PROJECT).h --enable=all --suppress=missingIncludeSystem --checkers-report=cc.txt $^

valgrind: $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -L. $(PROJECT).a $(LIBFLAGS) -o $(EXECUTABLE)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="log_valgrind.txt" ./$(EXECUTABLE)
	grep ERROR log_valgrind.txt
	make clean
	cat log_valgrind.txt

.PHONY: clean gcov_report clang-format rebuild cc

gtests: tests/test_s21_calc.cc s21_smart_calc.cc s21_smart_calc.h
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE) -lgtest -lgmock -pthread -lgtest_main
	clear
	./$(EXECUTABLE)