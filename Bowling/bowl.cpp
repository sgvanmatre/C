/*
Program is used to calcuate the score for bowling. 

By: Seth VanMatre
Last updated: 9/22/2021
*/

#include <iostream> 
#include "game.h"

int Game::score(){ 
  int score = 0; 
  for(int index = 0; index < 10; index++){

    if(strikeDetermine())
    {
      score += strikeIsRolled();
      rollIndex += 1; 
    }
    else if (spareDetermine()){
      score +=spareIsRolled();  
      rollIndex += 2;
    }
    else
    {
     score += scoreCalculation();  
     rollIndex += 2;
    }
    
  } 
  return score; 
}

void Game::roll(int numPins){
  this->frames[this->currentRoll] = numPins; 
  this->currentRoll += 1; 
}

int Game::spareIsRolled(){
  return this->frames[rollIndex] + this->frames[rollIndex + 1] + this->frames[rollIndex + 2];
}

int Game::scoreCalculation(){
  return this->frames[rollIndex] + this->frames[rollIndex + 1]; 
}

int Game::strikeIsRolled(){
  return frames[rollIndex] + this->frames[rollIndex + 1] + this->frames[rollIndex + 2]; 
}

bool Game::strikeDetermine(){
  return this->frames[rollIndex] == 10; 
}

bool Game::spareDetermine(){
  return this->frames[rollIndex] + this->frames[rollIndex +1] == 10; 
}



Game::Game(){
  
}

Game::~Game(){
  
}
 