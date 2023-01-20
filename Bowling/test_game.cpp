#include <iostream>
#include "gtest/gtest.h"
#include "game.h"

class bowlingTest : public testing::Test {
    protected:
        Game game;
};


TEST_F(bowlingTest, Score_Test){
  for(int i = 0; i < 20; i++){
    game.roll(1); 
  }
  ASSERT_EQ(20, game.score()); 
}

TEST_F(bowlingTest, Spare_Test){
  game.roll(8);
  game.roll(2);
  game.roll(3); 
  game.roll(0); 
  ASSERT_EQ(16, game.score()); 
}

TEST_F(bowlingTest, Strike_Test){
  game.roll(10);
  game.roll(10); 
  game.roll(3);
  ASSERT_EQ(39, game.score()); 
}

TEST_F(bowlingTest, roll_shortGame_Test){
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(0);
  ASSERT_EQ(240, game.score()); 
}

TEST_F(bowlingTest, roll_perfectGame_Test){
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  game.roll(10);
  ASSERT_EQ(300, game.score());
}

TEST_F(bowlingTest, roll_RandomGame_Test){
  game.roll(10);
  game.roll(9);
  game.roll(1);
  game.roll(5);
  game.roll(2);
  game.roll(10);
  game.roll(8);
  game.roll(2);
  game.roll(0);
  game.roll(0);
  game.roll(10);
  game.roll(5);
  game.roll(5);
  game.roll(10);
  game.roll(9);
  game.roll(1);
  game.roll(5);
  ASSERT_EQ(147, game.score());
}


int main(int argc, char **argv) {
  
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}