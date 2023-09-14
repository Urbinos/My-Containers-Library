CC=gcc -std=c++17
CFLAGS=-Wall -Werror -Wextra -lstdc++
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

TEST_PATH=./Google_tests/*
TEST_VECTOR=./Google_tests/s21_vector_test.cc
TEST_LIST=./Google_tests/s21_list_test.cc
TEST_QUEUE=./Google_tests/s21_queue_test.cc
TEST_ARRAY=./Google_tests/s21_array_test.cc
TEST_LIST=./Google_tests/s21_list_test.cc
TEST_STACK=./Google_tests/s21_stack_tests.cc
TEST_MAP=./Google_tests/s21_map_tests.cc

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=`pkg-config --cflags --libs gtest` -lpthread -lgtest -pthread -lrt -lm -lgmock
endif

all: clean test

test: clean 
	$(CC) $(CFLAGS) $(LIBFLAGS) $(TEST_PATH) -o test
	./test

gcov_report:
	$(CC) $(TEST_PATH) $(LIBFLAGS) $(GCOV_FLAGS) -lcheck -o test
	./test
	gcov test
	lcov --ignore-errors mismatch -t  "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml coverage.info --output-directory ./report/
	open ./report/index.html

leaks: test
	CK_FORK=no leaks --atExit -- ./test

clang: 
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n  *.h $(TEST_PATH)
	rm .clang-format

clean:
	@rm -rf *.a \
	*.o \
	*.info \
	*.gcda \
	*.gcno \
	*.gcov \
	*.gch  \
	report \
	test
