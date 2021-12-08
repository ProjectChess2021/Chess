// Kunling Yang
// Last Modified At (UTC-5) 1755, 20211208

#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__

#include "levelTwo.h"
#include "piece.h"

class LevelThree : public LevelTwo{
    public:
    std::string makeMove(std::vector<std::vector<Piece *>>&, std::vector<Move>&) override;
};  // end LevelThree

#endif
