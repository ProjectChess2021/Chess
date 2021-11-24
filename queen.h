// Kunling Yang, 20912628
// Last Modified At 0156, 20211123
// Concrete Derived Class of Piece (2/6)

#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
  public:
    virtual bool move();
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~Queen();
};  // end Queen

#endif
