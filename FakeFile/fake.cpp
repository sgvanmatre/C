#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <regex>

class ArgumentPassingExecption{
	public: 
		ArgumentPassingExecption(const std::string message, const int argsExtra, const int allowedArgs):
				message(message),argsExtra(argsExtra), allowedArgs(allowedArgs){}; 
		int getExtra() const{return (argsExtra); }
		std::string getMessage() const {return(message);}
		int argsAllowed()const { return allowedArgs;}
	private: 
		int argsExtra;
		int allowedArgs;
		std::string message; 
};

class ArgumentParser {
	public:
		ArgumentParser(int argc, char *argv[]){
			arguments = argv;
			numArgs = argc;
		}

		std::string parserFunction(){
			if(numArgs > 2){
				throw ArgumentPassingExecption(arguments[2], numArgs -1, 1);
			}else if(numArgs == 2){
				dependency = arguments[1];
			}
			return dependency;
		}
	private:
		char** arguments;
		int numArgs;
		std::string dependency = "";
};

class FileParserException{
	public:
		FileParserException(const std::string message, const int number):
			errorMessage(message), exitStatus(number){};

		std::string getMessage() const{
			return errorMessage;
		};

		int getNumber() const {
			return exitStatus;
		};

	private:
		int exitStatus;
		std::string errorMessage;
};

class CommandParserException{
	public:
		CommandParserException(const std::string message, const int number):
			errorMessage(message), exitStatus(number){};

		std::string getMessage() const{
			return errorMessage;
		};

		int getNumber() const {
			return exitStatus;
		};

	private:
		int exitStatus;
		std::string errorMessage;
};

class FileReaderExecptions{
	public:
		void checkTargetFound(bool found_target, std::string &one, std::string &target){
			if(!found_target){
				throw CommandParserException("No rule to make target '" + target + "', needed by '" + one + "'.", 1);
			}
		}
	
	void checkCommandListSize(std::vector<std::string> &commandsList){
		if(commandsList.size() == 0)
			throw CommandParserException("No targets.", 1); 
	}

	void checkCircularDependency(std::vector<std::string> &targetsList, std::string &one, std::string &two){
		if(std::find(targetsList.begin(), targetsList.end(), two) != targetsList.end()){
			std::cout << "fake: Circular " + one + " <- " + two + " dependency dropped.\n";
			two = "";
		}
	}

	void checkFileExists(std::ifstream &inFile, std::string &fileName){
		if (!inFile)
			throw(FileParserException(fileName + ":" + " No such file or directory", 1));
	}


}; 

class FileReader{
	private: 
		FileReaderExecptions execption; 
		std::string fileName;
		std::vector<std::string>  variablesList, commandsList;
		std::vector<int> linesList;
		std::stack<std::queue<std::string>> recipes;
		std::stack<std::string> targets;
		std::stack<std::queue<int>> lines;
		std::vector<std::string> targetsList;
		std::string one, two;
		bool found_target = false;

		void variableReplacer(){
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


		void pushTargetList_Targets(std::vector<std::string> &targetsList){
			for(int i=0; i < targetsList.size(); i++){
				targets.push(targetsList[i]);
			}
		}


		void readFromFile_Store_Vars_Coms_Lines(std::ifstream &inFile){
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

		bool hasDependancy(int &index){
			return (commandsList[index].find_first_of(':', 0) != -1); 
		} 

		bool commandHasTab(int &currentTargetLine){
			return (commandsList[currentTargetLine][0] == '\t'); 
		}


		void getStrings_One_Two(int &index){
					std::stringstream tempStream(commandsList[index]);
					std::getline(tempStream, one, ':');
					std::getline(tempStream, two, ':');
					one.erase(remove_if(one.begin(), one.end(), isspace), one.end());
					two.erase(remove_if(two.begin(), two.end(), isspace), two.end());
		}

		void loadQueue_line_temp(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue, int &currentTargetLine){
			while(currentTargetLine < commandsList.size() && commandHasTab(currentTargetLine)){
				tempQueue.push(commandsList[currentTargetLine].substr(1));
				lineQueue.push(linesList[currentTargetLine]);
				currentTargetLine++;
			}
		}

		void push_Recipes_Lines(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue){
			recipes.push(tempQueue);
			lines.push(lineQueue);
		}

		void reset_FoundTargets_Index(int &index){
			index = 0;
			found_target = false;
		}

		bool loadVariable(std::string &target, int &index){
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

		void readThroughFile(std::string &target){
			for(int i=0; i<commandsList.size(); i++){
				if(loadVariable(target, i))
					break; 
			}
			execption.checkTargetFound(found_target, one, target); 
			pushTargetList_Targets(targetsList); 
		}


	public:
		FileReader(std::string filename){
			fileName = filename;   
		}

		std::stack<std::queue<std::string>> returnRecipes(){
			return recipes; 
		}

		std::stack<std::string> returnTargets(){
			return targets; 
		}

		std::stack<std::queue<int>> returnLines(){
			return lines;
		}
		

		void get_recipes(std::string target){
			std::ifstream inFile(fileName);
			execption.checkFileExists(inFile, fileName); 
			readFromFile_Store_Vars_Coms_Lines(inFile); 

			variableReplacer();  			
			execption.checkCommandListSize(commandsList); 

			// I disagree, FileReader should be reading the file and in doing so storing the variables from the file. Although, I do agree that the file reader thowing execptions should be in a different class. 
			readThroughFile(target); 
			
		}
	

		
};

class CommandException{
	public:
		CommandException(const std::string message, const int exitStatus):
				message(message), exitStatus(exitStatus){};

		std::string getMessage() const{
			return message;
		}

		int getExitStatus() const{
			return exitStatus;
		}
	private:
		std::string message;
		int exitStatus;
};

class CommandData{
	private: 
	std::stack<std::queue<std::string>> args;
	std::stack<std::queue<int>> lines;
	std::stack<std::string> targets;
	std::queue<std::string> arg; 
	std::queue<int> line;
	std::string currentTarget;


	public:
		CommandData(std::stack<std::queue<std::string>> argsInput, std::stack<std::queue<int>> linesInput, std::stack<std::string> targetsInput){
			args = argsInput;
			lines = linesInput;
			targets = targetsInput;
		}

		void setArgLineCurTarget(){
		arg = args.top();
		line = lines.top();
		currentTarget = targets.top();
		}

		std::string getArgFront(){
			return arg.front(); 
		}

		int getLineFront(){
			return line.front(); 
		}

		std::string getCurrentTarget(){
			return currentTarget; 
		}

		void popLine_Arg(){
			line.pop();
			arg.pop();
		}

		void popArgs_Lines_Targets(){
			args.pop();
			lines.pop();
			targets.pop();
		}

		bool isArgsNotEmpty(){
			if(!args.empty())
				return true; 
			return false; 
		}

		bool isArgNotEmpty(){
			if(!arg.empty())
				return true; 
			return false; 
		}
		
		
}; 


class RunCommands: private CommandData{
	private:

		void recipeTargetFail(int status){
			std::cout << "Fakefile:" << getLineFront() << ": recipe for target '" << getCurrentTarget() << "' failed" <<  std::endl;
			throw CommandException("[" + getCurrentTarget() + "] Error", WEXITSTATUS(status)); 
		}

		void runCommands(){
				while(isArgsNotEmpty()){
				setArgLineCurTarget(); 
				while(isArgNotEmpty()){
					std::string currentArg = getArgFront();
					std::cout << currentArg << std::endl;
					int status = system(currentArg.c_str());
					if(WEXITSTATUS(status) != 0){
						recipeTargetFail(status); 
					}
					popLine_Arg(); 
				}
			 popArgs_Lines_Targets(); 
			}
		}
	
	public:
		RunCommands(std::stack<std::queue<std::string>> argsInput, std::stack<std::queue<int>> linesInput, std::stack<std::string> targetsInput): CommandData(argsInput, linesInput, targetsInput){
		runCommands(); 
		}

		

};

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
