#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <regex>
#include <fstream>
#include "FileReaderExceptionThrow.h"

class FileReader{
	private: 
		FileReaderExecptionThrow execption; 
		std::string fileName;
		std::vector<std::string>  variablesList, commandsList;
		std::vector<int> linesList;
		std::stack<std::queue<std::string>> recipes;
		std::stack<std::string> targets;
		std::stack<std::queue<int>> lines;
		std::vector<std::string> targetsList;
		std::string one, two;
		bool found_target = false;

		void variableReplacer();
		void pushTargetList_Targets(std::vector<std::string> &targetsList);
		void readFromFile_Store_Vars_Coms_Lines(std::ifstream &inFile);
		bool hasDependancy(int &index);

		bool commandHasTab(int &currentTargetLine);

		void getStrings_One_Two(int &index);

		void loadQueue_line_temp(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue, int &currentTargetLine);

		void push_Recipes_Lines(std::queue<std::string> &tempQueue, std::queue<int> &lineQueue);

		void reset_FoundTargets_Index(int &index);

		bool loadVariable(std::string &target, int &index);

		void readThroughFile(std::string &target);

	public:
		FileReader(std::string filename);

		std::stack<std::queue<std::string>> returnRecipes();

		std::stack<std::string> returnTargets();

		std::stack<std::queue<int>> returnLines();

		void get_recipes(std::string target);

};