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
    std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, const int) override;
};  // end LevelTwo

#endif
