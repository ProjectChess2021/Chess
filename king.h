#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King :public Piece {
    bool moved;
    public:
    King( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Posn *end ) override;
};

#endif