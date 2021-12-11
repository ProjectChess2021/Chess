// Kunling Yang
// Last Modified At (UTC-5) 2114, 20211203

#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include <utility>
#include "move.h"
#include <string>
#include <vector>
#include "game.h"


class Strategy {    
    public:
    virtual ~Strategy() = default;
    virtual std::string makeMove(Game&, std::vector<std::unique_ptr<Move>>&, 
        const int)  = 0;
};  // end Strategy

#endif
