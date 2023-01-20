#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED
#include <bits/stdc++.h> 

class myFibonacci{
	public:
    bool verboseConformation(std::string confirm); 
    int stringToIntConversion(std::string keyWord); 
    int seqencePrintDeterminate(std::string keyWord); 
    int seqenceCaculation(); 
    int seqencePrintToConsol();
    bool isNumber( std::string token ); 

  private:
    int n_Term, term1 = 0, term2 = 1, nextTerm = 0;

};
#endif