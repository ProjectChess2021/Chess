// Kunling Yang, 20912628
// Last Modified At 0151, 20211123
// Concrete Creator from Factory Design Pattern

#ifndef __BLACKSIDE_H__
#define __BLACKSIDE_H__

#include "side.h"

class BlackSide : public Side {
  public:
    virtual std::shared_ptr<Piece> spwanPiece();
};  // end BlackSide

#endif
