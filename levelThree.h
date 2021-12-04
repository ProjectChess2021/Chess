// Kunling Yang
// Last Modified At (UTC-5)1919, 20211203

#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__

#include "strategy.h"
#include "piece.h"

class LevelThree : public Strategy{
    public:
    void makeMove(std::vector<std::vector<Piece *>>&) override;
};  // end LevelThree

#endif
