#include "fib.h"
#include <string> 
#include <regex>

bool myFibonacci::verboseConformation(std::string confirm){
  if (confirm == "--verbose")
    return true; 
  else{
    myFibonacci::stringToIntConversion(confirm);
  }
  return false; 
}

int myFibonacci::stringToIntConversion(std::string keyWord){
  n_Term = std::stoi(keyWord); 
  return n_Term; 
}

int myFibonacci::seqencePrintDeterminate(std::string keyWord){
  if(myFibonacci::verboseConformation(keyWord)){
    myFibonacci::seqencePrintToConsol(); 
    return 1; 
   }
   else{
     std::cout<<myFibonacci::seqenceCaculation()<<std::endl; 
     return 2;
   } 
}

int myFibonacci::seqenceCaculation(){
 for(int i = 0; i < n_Term; i++){
   nextTerm = term1 + term2; 
     term1 = term2; 
     term2 = nextTerm; 
   }
   return nextTerm; 
}

int myFibonacci::seqencePrintToConsol(){
  std::cout<<term1 << ", " << term2 << ", "; 
  for(int i = 0; i < n_Term; i++){
     nextTerm = term1 + term2; 
     term1 = term2; 
     term2 = nextTerm; 
     std::cout<<nextTerm << ", "; 
   }
  std::cout << " " << std::endl; 
  return nextTerm; 
}

//Got this function from online. 
bool myFibonacci::isNumber( std::string token )
{
    return std::regex_match( token, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) );
}

