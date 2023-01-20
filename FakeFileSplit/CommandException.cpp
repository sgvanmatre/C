#include <iostream>
#include "CommandException.h"


CommandException::CommandException(const std::string message, const int exitStatus): message(message), exitStatus(exitStatus){};
std::string CommandException::getMessage() const{return message;}
int CommandException::getExitStatus() const{return exitStatus;}
