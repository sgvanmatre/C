INSTALL=install
OBJS=$(INSTALL)/objs
BIN=$(INSTALL)/bin
GTEST_ROOT=/home/runner/222/googleTest
GTEST_INC=$(GTEST_ROOT)/include
GTEST_LIB=$(GTEST_ROOT)/lib


test: square.o
	g++ -o $(BIN)/test_square -I$(GTEST_INC) test_square.cpp ${OBJS}/square.o $(GTEST_LIB)/libgtest.a

square.o: setup
	g++ -c -o $(OBJS)/square.o square.cpp

setup: clean
	mkdir -p $(OBJS)
	mkdir -p $(BIN)

clean:
	rm -rf $(INSTALL)
