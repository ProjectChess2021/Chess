#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
    public:
    Pawn( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        Game &game ) override;
};

#endif