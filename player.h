// Zichu
// Last Modified At (UTC-5) 1032, 20211208 (By Kunling)

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "piece.h"
#include "move.h"
#include "observer.h"

class Player : public Observer {
    float score;
    int id;
    std::vector<Move> availableMove;
    void emplacePieceMove(const int, const int, Game &game);
    public:
    Player( const int &id );
    void notify( Game &game ) override;
    float &getScore();
    int getId();
    bool hasAvaliableMove();
    virtual std::string cmd( Game &game ) = 0;
    virtual ~Player();
};

#endif
