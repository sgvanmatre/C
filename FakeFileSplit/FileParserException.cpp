#include <iostream>
#include "FileParserException.h"

FileParserException::FileParserException(const std::string message, const int number):
errorMessage(message), exitStatus(number){};
std::string FileParserException::getMessage() const {return errorMessage;}
int FileParserException::getNumber() const {return exitStatus;}

