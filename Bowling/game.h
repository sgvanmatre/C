#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Game
{
	public:
	    Game();
	    ~Game();
	    void roll(int numPins);
	    int score();

  private: 
  int frames[20]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
  rollIndex = 0, currentRoll = 0; 

  int scoreCalculation();
  bool strikeDetermine();
  bool spareDetermine();  
  int spareIsRolled();
  int strikeIsRolled();  

};

#endif