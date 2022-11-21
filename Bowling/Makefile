INSTALL=install
OBJS=$(INSTALL)/objs
BIN=$(INSTALL)/bin
GTEST_ROOT=/home/runner/BowlingScore/googleTest
GTEST_INC=$(GTEST_ROOT)/include
GTEST_LIB=$(GTEST_ROOT)/lib

  
test: game.o
	g++ -o $(BIN)/test_game -I$(GTEST_INC) test_game.cpp ${OBJS}/game.o $(GTEST_LIB)/libgtest.a

	
game.o: setup
	g++ -c -o $(OBJS)/game.o bowl.cpp

setup: clean
	mkdir -p install/Exe
	mkdir -p $(OBJS)
	mkdir -p $(BIN)

clean:
	rm -rf $(INSTALL)
