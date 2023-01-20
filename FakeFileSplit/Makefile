  
run: FileReader.o
	g++ -o $(BIN)/~/fake ${OBJS}/FileReader.o  ${OBJS}/ArgumentParser.o ${OBJS}/Exceptions.o ${OBJS}/ArgumentPassingException.o ${OBJS}/CommandException.o ${OBJS}/CommandParserException.o ${OBJS}/FileParserException.o ${OBJS}/FileReaderExceptionThrow
	
ArgumentParser.o: FileReader.o
	g++ -c -o $(OBJS)/ArgumentParser.o ArgumentParser.cpp

FileReader.o: Exceptions.o
	g++ -c -o $(OBJS)/FileReader.o FileReader.cpp
	
Exceptions.o: ArgumentPassingException.o
	g++ -c -o $(OBJS)/Exceptions.o Exceptions.cpp

ArgumentPassingException.o: CommandException.o
	g++ -c -o $(OBJS)/ArgumentPassingException.o ArgumentPassingException.cpp

CommandException.o: CommandParserException.o 
	g++ -c -o $(OBJS)/CommandException.o CommandException.cpp

CommandParserException.o: FileParserException.o
	g++ -c -o $(OBJS)/CommandParserException.o CommandParserException.cpp

FileParserException.o: FileReaderExceptionThrow.o
	g++ -c -o $(OBJS)/FileParserException.o FileParserException.cpp
	
FileReaderExceptionThrow.o: setup
	g++ -c -o $(OBJS)/FileReaderExceptionThrow.o FileReaderExceptionThrow.cpp

setup: clean
	mkdir -p $(OBJS)
	mkdir -p $(BIN)

clean:
	rm -rf $(INSTALL)
	clear