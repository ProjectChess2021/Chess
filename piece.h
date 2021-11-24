// Kunling Yang, 20912628
// Last Modified at 0230, 20211123
// Abstract Base Class of Piece

#ifndef __PIECE_H__
#define __PIECE_H__

#include <memory>

class PieceImpl;    // forward declaration
class Visitor;
class Posn;

class Piece {
  protected:
    std::unique_ptr<PieceImpl> pImpl;               // Bridge design pattern
  public:
    virtual bool move() = 0;
    virtual void capturedBy(Visitor&) = 0;          // visitor design pattern
    virtual ~Piece();
};


#endif
