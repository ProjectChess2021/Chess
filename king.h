#ifndef __KING_H__
#define __KING_H__

#include "piece.h"
#include "posn.h"

class King :public Piece {
    public:
    King( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) override;
};

#endif
