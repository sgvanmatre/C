#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "FileReaderExceptionThrow.h"
#include "CommandParserException.h"
#include "FileParserException.h"



void FileReaderExecptionThrow::checkTargetFound(bool found_target, std::string &one, std::string &target){
	if(!found_target){
		throw CommandParserException("No rule to make target '" + target + "', needed by '" + one + "'.", 1);
	}
}

void FileReaderExecptionThrow::checkCommandListSize(std::vector<std::string> &commandsList){
	if(commandsList.size() == 0)
		throw CommandParserException("No targets.", 1); 
}

void FileReaderExecptionThrow::checkCircularDependency(std::vector<std::string> &targetsList, std::string &one, std::string &two){
		if(std::find(targetsList.begin(), targetsList.end(), two) != targetsList.end()){
			std::cout << "fake: Circular " + one + " <- " + two + " dependency dropped.\n";
			two = "";
	}
}

void FileReaderExecptionThrow::checkFileExists(std::ifstream &inFile, std::string &fileName){
		if (!inFile)
			throw(FileParserException(fileName + ":" + " No such file or directory", 1));
}
