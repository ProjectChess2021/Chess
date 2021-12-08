// Kunling Yang
// Last Modified At (UTC-5) 1918, 20211203

#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__

#include "strategy.h"
#include "levelOne.h"
#include "piece.h"
#include <vector>

class LevelTwo : public LevelOne{
    public:
    std::string makeMove(std::vector<std::vector<Piece *>>&, std::vector<Move>&) override;
};  // end LevelTwo

#endif
