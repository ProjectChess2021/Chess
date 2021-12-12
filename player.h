// Zichu
// Last Modified At (UTC-5) 1939,20211210 (By Kunling)

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <memory>
#include "piece.h"
#include "move.h"
#include "observer.h"

class Game;

class Player : public Observer {
    float score;
    int id,numUndo;
    std::vector<std::unique_ptr<Move>> availableMove;
    void emplacePieceMove( const int x, const int y, 
        std::vector<std::vector<Piece *>> &b, MoveHistory &mh );
    public:
    Player(const int, const float score = 0);
    void notify( std::vector<std::vector<Piece *>> &b, 
        MoveHistory &mh ) override;
    float &getScore();
    int getId();
    int getNumUndo();
    void changeUndo( const int num );
    void usedUndo();
    bool hasAvaliableMove();        // return true if this player still has possible movement, false otherwise
    virtual std::string cmd( Game &game ) = 0;
    virtual char promptTo() = 0;
    virtual ~Player();
    std::vector<std::unique_ptr<Move>>& getAM();
};

#endif
