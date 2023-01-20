class CommandException{
	public:
		CommandException(const std::string message, const int exitStatus);

		std::string getMessage() const;

		int getExitStatus() const;
	private:
		std::string message;
		int exitStatus;
};
