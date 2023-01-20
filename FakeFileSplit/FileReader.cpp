#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <regex>
#include <fstream>
#include "FileReader.h"


void FileReader::variableReplacer(){
			for(int i=0; i<variablesList.size(); i++){
				std::stringstream temp(variablesList[i]);
				std::string variable;
				std::string value;
				std::getline(temp, variable, '=');
				std::getline(temp, value, '=');
				variable.erase(remove_if(variable.begin(), variable.end(), isspace), variable.end());
				value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
				std::regex token("\\$\\{" + variable + "\\}");
				for(int i=0; i<commandsList.size(); i++){
					commandsList[i] = std::regex_replace(commandsList[i], token, value);
		}
	}
}

void FileReader::pushTargetList_Targets(std::vector<std::string> &targetsList){
		for(int i=0; i < targetsList.size(); i++){
			targets.push(targetsList[i]);
	}
}

void FileReader::readFromFile_Store_Vars_Coms_Lines(std::ifstream &inFile){
			std::string line;
			int i = 0;
			while(std::getline(inFile, line)){
				i++;
				if (line == "") {
					continue;
				} else if (line.find_first_of('=', 0) != -1) {
					variablesList.push_back(line);
				} else{
					commandsList.push_back(line);
					linesList.push_back(i);
				}
			}
}

bool FileReader::hasDependancy(int &index){
			return (commandsList[index].find_first_of(':', 0) != -1); 
		} 

bool FileReader::commandHasTab(int &currentTargetLine){
	return (commandsList[currentTargetLine][0] == '\t'); 
}

void FileReader::getStrings_One_Two(int &index){
		std::stringstream tempStream(commandsList[index]);
		std::getline(tempStream, one, ':');
		std::getline(tempStream, two, ':');
		one.erase(remove_if(one.begin(), one.end(), isspace), one.end());
		two.erase(remove_if(two.begin(), two.end(), isspace), two.end());
}

void FileReader::loadQueue_line_temp(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue, int &currentTargetLine){
			while(currentTargetLine < commandsList.size() && commandHasTab(currentTargetLine)){
				tempQueue.push(commandsList[currentTargetLine].substr(1));
				lineQueue.push(linesList[currentTargetLine]);
				currentTargetLine++;
			}
}

void FileReader::push_Recipes_Lines(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue){
			recipes.push(tempQueue);
			lines.push(lineQueue);
}

void FileReader::reset_FoundTargets_Index(int &index){
			index = 0;
			found_target = false;
		}

	bool FileReader::loadVariable(std::string &target, int &index){
				std::queue<std::string> tempQueue;
				std::queue<int> lineQueue;
				if(hasDependancy(index)){
					getStrings_One_Two(index); 
					if(one == target || target == ""){
						found_target = true;
						targetsList.push_back(one);
						int currentTargetLine = index + 1;
						loadQueue_line_temp(tempQueue, lineQueue, currentTargetLine); 
						push_Recipes_Lines(tempQueue, lineQueue); 
						execption.checkCircularDependency(targetsList, one, two); 
						if(two == "")
							return true;
						target = two;
					reset_FoundTargets_Index(index); 
					}
				}
			return false; 
		}

void FileReader::readThroughFile(std::string &target){
			for(int i=0; i<commandsList.size(); i++){
				if(loadVariable(target, i))
					break; 
			}
			execption.checkTargetFound(found_target, one, target); 
			pushTargetList_Targets(targetsList); 
		}

FileReader::FileReader(std::string filename){
	fileName = filename;   
}

std::stack<std::queue<std::string>> FileReader::returnRecipes(){
	return recipes; 
}

std::stack<std::string> FileReader::returnTargets(){
			return targets; 
		}

std::stack<std::queue<int>> FileReader::returnLines(){
	return lines;
}

void FileReader::get_recipes(std::string target){
			std::ifstream inFile(fileName);
			execption.checkFileExists(inFile, fileName); 
			readFromFile_Store_Vars_Coms_Lines(inFile); 

			variableReplacer();  			
			execption.checkCommandListSize(commandsList); 

			// I disagree, FileReader should be reading the file and in doing so storing the variables from the file. Its a waste of memory if I just add a new class that then stores all the elements when I can do it in FileReader. Although, I do agree that the file reader expections should be in a different class. 
			readThroughFile(target); 
			
		}