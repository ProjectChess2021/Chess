#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
    public:
    Queen( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Posn *end ) override;
};

#endif