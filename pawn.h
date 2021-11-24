// Kunling Yang, 20912628
// Last Modified At 0159, 20211123
// Concrete Derived Class of Piece (6/6)

#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
  public:
    virtual bool move();                // inherited move
    virtual void capturedBy(Visitor&);  // adapt visitor design pattern
    virtual ~Pawn();

    // Unqiue Ability of Pawn
    void prompt();

};  // end Pawn

#endif
