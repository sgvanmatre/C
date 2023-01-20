#include "Exceptions.h"
class ArgumentParser {
	public:
		ArgumentParser(int argc, char *argv[]);

		std::string parserFunction();
	private:
		char** arguments;
		int numArgs;
		std::string dependency = "";
};