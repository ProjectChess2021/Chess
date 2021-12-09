#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"
#include "posn.h"

class Bishop : public Piece {
    public:
    Bishop( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        Game &game ) override;
};

#endif