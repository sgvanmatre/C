INSTALL=install
OBJS=$(INSTALL)/objs
BIN=$(INSTALL)/bin
GTEST_ROOT=/home/runner/Fibonacci11/GoogleTest/googleTest
GTEST_INC=$(GTEST_ROOT)/include
GTEST_LIB=$(GTEST_ROOT)/lib


test: fib.o
	g++ -o $(BIN)/test_fib -I$(GTEST_INC) test_fib.cpp ${OBJS}/fib.o $(GTEST_LIB)/libgtest.a

fib.o: setup
	g++ -c -o $(OBJS)/fib.o fib.cpp

setup: clean
	mkdir -p $(OBJS)
	mkdir -p $(BIN)

clean:
	rm -rf $(INSTALL)
