// Kunling Yang, 20912628
// Last Modified At 1857, 20211124
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "posn.h"
#include "subject.h"
#include "moveHistory.h"
#include "piece.h"

class Player;

class Game : public Subject {
    std::vector<Player *> players;
    std::unique_ptr<MoveHistory> mh;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<std::vector<Piece *>> board;
    std::vector<Piece *> deadPool;
    bool isChecked( const int &x, const int &y, const int &side );
  public: 
    Game( std::vector<Player *> *players );
    // Use board and movehistory in start, which is in each game
    void play();
    char move( Posn *original, Posn *end );
    char undo( Posn *end, Posn *original );
    void displayScore();
    void setup();
};  // end Game

#endif
