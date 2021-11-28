#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
    bool moved;
    public:
    Pawn( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Posn *end ) override;
};

#endif