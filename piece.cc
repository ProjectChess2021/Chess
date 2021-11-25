// Kunling Yang, 20912628
// Last Modified At 1730,20211124

#include "piece.h"
#include "position.h"

class PieceImpl{
  protected:
    std::unique_ptr<Posn> pos;
    bool isEverMoved;
    virtual bool isValidMove(Posn&) = 0;
  public:
    PieceImpl(Posn&);
};  // end PieceImpl

