// Kunling Yang
// Last Modified At (UTC-5) 1755, 20211208

#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__

#include "levelTwo.h"
#include "piece.h"

class LevelThree : public LevelTwo{
    public:
    std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, const int) override;
};  // end LevelThree

#endif
