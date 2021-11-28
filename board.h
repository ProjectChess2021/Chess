// Kunling Yang, 20912628
// Last Modified At 1853, 20211124

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <memory>
#include "posn.h"
#include "subject.h"

class Piece;

class Board : public Subject {
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    std::vector<std::unique_ptr<Piece *>> deadPool;
  public:
    Board();
    void setup();
    
    char move( Posn *original, Posn *final );
    char undo( Posn *final, Posn *original );
};  // end Board

#endif
