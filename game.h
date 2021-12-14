// Kunling Yang, 20912628
// Last Modified At 0007, 20211201

#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "subject.h"
#include "player.h"
#include "moveHistory.h"
#include "piece.h"
#include "board.h"

class Player;

class Game : public Subject {
    std::vector<Player *> players;
    std::unique_ptr<MoveHistory> mh;
    std::unique_ptr<Board> b;
    bool whiteStart, isSetup;
    void goOn();
    void errorMsg();
    void move( const int &originalX, const int &originalY, 
    const int &endX, const int &endY, const int id );
    void undo();
    bool isValidSetup(const int, const int, std::string&);
  public: 
    Game();
    // Use board and movehistory in start, which is in each game
    void start();
    void setup();
    void boardInit();

    std::vector<Player*>& getPlayers();
    std::vector<std::vector<Piece *>> &getBoard();
    Board& getb();
    MoveHistory*getMoveHistory();
    float getScore(int idx);  // return the currentScore of a single player
    void addPlayer( Player *player );
    Player* nextPlayer(int currId);
    void clearPlayer();
};  // end Game

#endif
