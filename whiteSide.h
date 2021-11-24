// Kunling Yang, 20912628
// Last Modified At 0150, 20211123
// Concrete Creator from Factory Design Pattern

#ifndef __WHITESIDE_H__
#define __WHITESIDE_H__

#include "side.h"

class WhiteSide : public Side {
  public:
    virtual std::shared_ptr<Piece> spwanPiece();
};  // end WhiteSide

#endif
