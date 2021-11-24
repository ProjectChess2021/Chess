// Kunling Yang, 20912628
// Last Modified At 0234, 20211123
// Concrete Derived Class of Piece (4/6)

#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class King;
class Rook : public Piece {
    bool isValidCastling(King&);
  public:
    virtual bool move();
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~Rook();

    // Unique Ability of Rook
    void Castling();
};  // end Rook

#endif
