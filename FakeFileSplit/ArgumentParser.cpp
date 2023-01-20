#include <iostream>
#include "Exceptions.h"
#include "ArgumentParser.h"
#include "ArgumentPassingExecption.h"


ArgumentParser::ArgumentParser(int argc, char *argv[]){
			arguments = argv;
			numArgs = argc;
}

std::string ArgumentParser::parserFunction(){
			if(numArgs > 2){
				throw ArgumentPassingExecption(arguments[2], numArgs -1, 1);
			}else if(numArgs == 2){
				dependency = arguments[1];
			}
			return dependency;
		}