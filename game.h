// Kunling Yang, 20912628
// Last Modified At 0007, 20211201

#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "subject.h"
#include "player.h"
#include "moveHistory.h"
#include "rook.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "piece.h"

class Game : public Subject {
    std::vector<Player *> players;
    std::unique_ptr<MoveHistory> mh;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<std::vector<Piece *>> board;
    std::vector<Piece *> deadPool;
    bool whiteStart,isSetup;

    // will not change the moved status of the piece that is being changed
    std::string move( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY );
    void undo();
    bool isValidSetup(const int, const int, std::string&);
  public: 
    Game();
    // Use board and movehistory in start, which is in each game
    void start();
    void setup();
    void boardInit();

    std::vector<Player*>& getPlayers();
    std::vector<std::vector<Piece *>>& getBoard();
    MoveHistory*getMoveHistory();
    float getScore(int idx);  // return the currentScore of a single player
    void addPlayer( Player *player );
};  // end Game

#endif
