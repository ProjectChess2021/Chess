// Kunling Yang, 20912628
// Last Modified At 1853, 20211124

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <memory>
#include "position.h"

class Piece;

class Board {
    std::vector<Piece> pieceArray;
  public:
    Board();
    void setUp();
};  // end Board

#endif
