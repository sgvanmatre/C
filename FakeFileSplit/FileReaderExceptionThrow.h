class FileReaderExecptionThrow{
	public:
		void checkTargetFound(bool found_target, std::string &one, std::string &target);
	
	void checkCommandListSize(std::vector<std::string> &commandsList);

	void checkCircularDependency(std::vector<std::string> &targetsList, std::string &one, std::string &two);

	void checkFileExists(std::ifstream &inFile, std::string &fileName);


}; 