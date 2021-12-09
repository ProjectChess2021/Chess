#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece {
    public:
    Rook( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        Game &game ) override;
};

#endif