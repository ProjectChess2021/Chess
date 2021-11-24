// Kunling Yang, 20912628
// Last Modified At 0157, 20211123
// Concrete Derived Class of Piece (3/6)

#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop : public Piece {
  public:
    virtual bool move();
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~Bishop();
};  // end Bishop

#endif
