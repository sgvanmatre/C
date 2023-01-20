class FileParserException{
	public:
		FileParserException(const std::string message, const int number);

		std::string getMessage() const;

		int getNumber() const;

	private:
		int exitStatus;
		std::string errorMessage;
};
