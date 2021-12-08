// Kunling Yang
// Last Modified At (UTC-5)1905, 20211203

#ifndef __LEVELONE_H__
#define __LEVELONE_H__

#include "strategy.h"
#include "piece.h"

class LevelOne : public Strategy{
    public:
    std::string makeMove(std::vector<std::vector<Piece *>>&, std::vector<Move>&) override;
};  // end LevelOne

#endif
