// Kunling Yang
// Last Modified At (UTC-5) 1904, 20211210

#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__

#include "strategy.h"
#include "piece.h"

class LevelFour : public Strategy{
    std::string cmd;
    int AlphaBeta(Game&, Player* currPlayer, int maxmizedID, int depth, int alpha, int beta);
    public:
    std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, const int) override;
};  // end LevelThree

#endif
