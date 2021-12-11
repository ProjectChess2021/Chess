// Zichu
// Last Modified At (UTC-5) 1939,20211210 (By Kunling)

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <memory>
#include "piece.h"
#include "move.h"
#include "observer.h"

class Player : public Observer {
    float score;
    int id,side,numUndo;
    std::vector<std::unique_ptr<Move>> availableMove;
    void emplacePieceMove(const int, const int, Game &game);
    public:
    Player( const int id, const int numUndo );
    Player(const int, const int, const int);  //tean specified
    void notify( Game &game ) override;
    float &getScore();
    int getId();
    int getSide();
    int getNumUndo();
    void usedUndo();
    bool hasAvaliableMove();        // return true if this player still has possible movement, false otherwise
    virtual std::string cmd( Game &game ) = 0;
    virtual ~Player();
    std::vector<std::unique_ptr<Move>>& getAM();
};

#endif
