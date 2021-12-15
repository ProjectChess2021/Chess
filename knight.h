#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"
#include "posn.h"

class Knight : public Piece {
    public:
    Knight( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) override;
};

#endif
