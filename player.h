// Zichu
// Last Modified At (UTC-5) 1032, 20211208 (By Kunling)

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "piece.h"
#include "move.h"
#include "observer.h"

class Player : public Observer {
    int score;
    int id;
    std::vector<Move> availableMove;
    std::vector<std::vector<Piece *>>& board;
    void emplacePieceMove(const int, const int);
    public:
    Player( const int &id, std::vector<std::vector<Piece *>>&);
    void notify() override;
    int getScore();
    int getId();
    virtual std::string cmd( std::vector<std::vector<Piece *>> board ) = 0;
    virtual ~Player();
};

#endif
