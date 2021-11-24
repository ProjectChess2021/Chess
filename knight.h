// Kunling Yang, 20912628
// Last Modified At 0159, 20211123
// Concrete Derived Class of Piece (5/6)

#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece {
  public:
    virtual bool move();
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~Knight();
};  // end Knight

#endif
