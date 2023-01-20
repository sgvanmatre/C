#include "gtest/gtest.h"
#include "fib.h"
#include <string> 



TEST(FibTest, verbose_Tester){
  myFibonacci myFib; 
  ASSERT_EQ(true, myFib.verboseConformation("--verbose"));
  ASSERT_EQ(false, myFib.verboseConformation("2")); 
}

TEST(FibTest, stringToIn_Test){
  myFibonacci myFib; 
  ASSERT_EQ(5, myFib.stringToIntConversion("5"));
}


TEST(FibTest, seqence_Calculation_Test){
  myFibonacci myFib;
  myFib.stringToIntConversion("5"); 
  ASSERT_EQ(8, myFib.seqenceCaculation());
}


TEST(FibTest, seqence_Determinate_Test){
  myFibonacci myFib;
  ASSERT_EQ(1, myFib.seqencePrintDeterminate("--verbose"));
  ASSERT_EQ(2, myFib.seqencePrintDeterminate("5"));
}

TEST(FibTest, seqence_Print_Test){
  myFibonacci myFib;
  myFib.stringToIntConversion("5"); 
  ASSERT_EQ(8, myFib.seqencePrintToConsol()); 
}


TEST(FibTest, checkStringIsNumber_Test){
  myFibonacci myFib; 
  ASSERT_EQ(true, myFib.isNumber("6"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}