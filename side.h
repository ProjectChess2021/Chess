// Kunling Yang
// Last Modified At 0147, 20211123
// Factory Design Pattern

#ifndef __SIDE_H__
#define __SIDE_H__

#include <memory>
class SideImpl;   // forward declarations
class Piece;

class Side{
  public:
    virtual std::shared_ptr<Piece>  spwanPiece() const = 0;  // ******
    virtual ~Side();
};  //end Side

#endif
