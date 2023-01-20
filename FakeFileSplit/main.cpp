#include <iostream>
#include "ArgumentParser.h"
#include "CommandException.h"
#include "FileParserException.h"
#include "CommandParserException.h"
#include "ArgumentPassingExecption.h"
#include "FileReader.h"
#include "RunCommands.h"

int main(int argc, char *argv[]){
	ArgumentParser parser = ArgumentParser(argc, argv);
	try{
		std::string target = parser.parserFunction();
		std::string file_name = "Fakefile";
		FileReader fileContent(file_name);
		try{
			fileContent.get_recipes(target);
			try{
				RunCommands runner(fileContent.returnRecipes(), fileContent.returnLines(), fileContent.returnTargets());
			}catch(CommandException& e){
				std::cout << "*** fake: " << e.getMessage() << " " << e.getExitStatus() << std::endl;
			}
		}catch(FileParserException& e){
			std::cout << "fake: " << e.getMessage() << std::endl;
			std::cout << "*** fake: " << "No rule to make target '" + file_name + "'." << " Stop." << std::endl;
			return 2;
		}catch(CommandParserException& e){
			std::cout << "*** fake: " << e.getMessage() << " Stop." << std::endl;
			return 2;
		}
	}catch(ArgumentPassingExecption& e){
		std::cout << "*** fake: Unrecognized argument " << e.getMessage() << std::endl;
		std::cout << "*** fake: Called with " << e.getExtra() << " arguments, " << e.argsAllowed() << " allowed\n";
		return 2;
	}
	
	return 0;
}
