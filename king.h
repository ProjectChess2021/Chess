// Kunling Yang, 20912628
// Last Modified At 0245, 20211123
// Concrete Derived Class of Piece (1/6)

#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class Rook;
class King : public Piece {
    virtual bool isValidCastling(Rook&);
    bool isChecked();
  public:
    virtual bool move();
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~King();

    // Unique Ability of King
    void castling();
};  // end King

#endif
