class ArgumentPassingExecption{
	public: 
		ArgumentPassingExecption(const std::string message, const int argsExtra, const int allowedArgs); 
		int getExtra() const; 
		std::string getMessage() const; 
		int argsAllowed()const;
	private: 
		int argsExtra;
		int allowedArgs;
		std::string message; 
};
