// Kunling Yang, 20912628
// Last Modified at 0230, 20211123
// Abstract Base Class of Piece

#ifndef __PIECE_H__
#define __PIECE_H__

#include <memory>
#include "posn.h"

class Piece {
    int side;
    static char type;
  public:
    Piece( const int &side, bool moved, const char &type );
    int getSide();
    char getType();
    virtual bool isValidMove( Posn *original, Posn *end ) = 0;
    virtual ~Piece();
};


#endif
