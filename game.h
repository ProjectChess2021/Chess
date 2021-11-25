// Kunling Yang, 20912628
// Last Modified At 1857, 20211124
#ifndef __GAME_H__
#define __GAME_H__

#include <memory>
#include <stack>
#include "board.h"

class Player;

class Game {
    std::unique_ptr<Board> aBoard;
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;
    bool undoable;
    std::stack<Piece> moveHistory;  
  public:
    Game(bool,std::unique_ptr<Player>,std::unique_ptr<Player>);
    void displayScore();
    void setUp(bool default);
};  // end Game

#endif
