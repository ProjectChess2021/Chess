// Kunling Yang, 20912628
// Last Modified At 0007, 20211201

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

    char move( Posn *original, Posn *end, char type );
    char undo( Posn *end, Posn *original, char type );

  public: 
    Game( std::vector<Player *> &players );
    // Use board and movehistory in start, which is in each game
    void start();
    void setup();

    std::vector<std::vector<Piece *>>& getBoard();
    std::unique_ptr<MoveHistory> getMoveHistory();
    int getScore(int idx);  // return the currentScore of a single player
};  // end Game

#endif
