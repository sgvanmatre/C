#include <iostream>
#include <stack>
#include <queue>
#include "Exceptions.h"

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


