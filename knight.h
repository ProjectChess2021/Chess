#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece {
    public:
    Knight( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Posn *end ) override;
};

#endif