// Kunling Yang, 20912628
// Last Modified At 0232, 20211123

#include "piece.h"

class PieceImpl{
  protected:
    std::unique_ptr<Posn> pos;
    bool isEverMoved;
    virtual bool isValidMove(Posn&) = 0;
  public:
    PieceImpl(Posn&);
};  // end PieceImpl

