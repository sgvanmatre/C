/*
Program uses header file "fib.h" to calculate the fibonacci seqence at the nth term.

Command line inputs: ./install/bin/fibExe --verbose (nth term)
                                    or 
                    ./install/bin/fibExe (nth term)
  
  Created By: Seth VanMatre
  Last updated: 9/15/2021
*/

#include <iostream>
#include "fib.h"

//Function declaration
void commandLineTry(int argc, char* argv[]); 

int main(int argc, char* argv[]) {  

  commandLineTry(argc, argv); 

  return 0; 
}

//Set what has been inputed by the command line to strings then try to see if one the first argument is a number. If not try to see if the secound argument is a number and the first is "--verbose".  
void commandLineTry(int argc, char* argv[]){
  myFibonacci myFib;

  std::string keyWord = argv[1];
  std::string nthTerm = argv[2]; 
  
  try{
    if(myFib.isNumber(keyWord)){
      myFib.seqencePrintDeterminate(keyWord); 
    }
    else if((myFib.isNumber(nthTerm) && myFib.verboseConformation(keyWord))){
      myFib.stringToIntConversion(nthTerm); 
      myFib.seqencePrintDeterminate(keyWord);
    }
    else
      throw; 
  }
  catch(...){
    std::cout<<"Error, invalid arguments" << std::endl;  
  }
}