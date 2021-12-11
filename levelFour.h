// Kunling Yang
// Last Modified At (UTC-5) 1904, 20211210

#ifndef __LEVELFOUR_H__
#define __LEVELFOUR_H__

#include "strategy.h"
#include "piece.h"

class LevelFour : public Strategy{
    public:
    std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, const int) override;
};  // end LevelThree

#endif
