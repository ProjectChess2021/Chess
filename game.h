// Kunling Yang, 20912628
// Last Modified At 1857, 20211124
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "Posn.h"
#include "subject.h"
#include "moveHistory.h"

class Player;

class Game : public Subject {
    std::vector<Player *> players;
    std::vector<std::vector<std::unique_ptr<Piece *>>> board;
    std::vector<std::unique_ptr<Piece *>> deadPool;
  public: 
    Game( std::vector<Player *> *players );
    // Use board and movehistory in start, which is in each game
    void start();
    char move( Posn *original, Posn *final );
    char undo( Posn *final, Posn *original );
    void displayScore();
    void setup();
};  // end Game

#endif
