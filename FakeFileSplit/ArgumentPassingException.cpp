#include <iostream>
#include "ArgumentPassingExecption.h"

ArgumentPassingExecption::ArgumentPassingExecption(const std::string message, const int argsExtra, const int allowedArgs): message(message),argsExtra(argsExtra), allowedArgs(allowedArgs){}; 
int ArgumentPassingExecption::getExtra() const{return (argsExtra); }
std::string ArgumentPassingExecption::getMessage() const {return(message);}
int ArgumentPassingExecption::argsAllowed()const { return allowedArgs;}