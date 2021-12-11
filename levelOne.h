// Kunling Yang
// Last Modified At (UTC-5) 1907, 20211210

#ifndef __LEVELONE_H__
#define __LEVELONE_H__

#include "strategy.h"
#include "piece.h"

class LevelOne : public Strategy{
    public:
    std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, 
        const int) override;
    ~LevelOne() = default;
};  // end LevelOne

#endif
