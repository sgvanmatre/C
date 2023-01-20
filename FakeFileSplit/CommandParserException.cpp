#include <iostream>
#include "CommandParserException.h"

CommandParserException::CommandParserException(const std::string message, const int number): errorMessage(message), exitStatus(number){};
std::string CommandParserException::getMessage() const{return errorMessage;}
int CommandParserException::getNumber() const {return exitStatus;}