// Kunling Yang, 20912628
// Last Modified At 1857, 20211124
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "board.h"
#include "moveHistory.h"

class Player;

class Game {
    std::vector<Player *> players;
  public: 
    Game( std::vector<Player *> *players );
    // Use board and movehistory in start, which is in each game
    void start();
    void displayScore();
    void setup();
};  // end Game

#endif
