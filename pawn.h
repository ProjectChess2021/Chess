#ifndef __PAWN_H__
#define __PAWN_H__

#include "Piece.h"

class Pawn : public Piece {
    bool moved;
    public:
    Pawn( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Pasn *end ) override;
};

#endif