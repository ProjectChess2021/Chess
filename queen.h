#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
    public:
    Queen( const int &side );
    bool isValidMove( Posn *original, Posn *end, 
        std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) override;
};

#endif
