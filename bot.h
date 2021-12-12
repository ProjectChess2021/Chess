// Zichu
// Last Modified At 1858, 20211203 (By Kunling Yang)

#ifndef __BOT_H__
#define __BOT_H__

#include "player.h"
#include <memory>

class Strategy;
class Bot : public Player {
    std::unique_ptr<Strategy> _strategy;
    public:
    Bot(const int _id, const int level, const float score);
    void setStrategy(const int);        // change the strategy, which is the AI difficulty
    std::string cmd( Game &game ) override;
    char promptTo() override;
};

#endif
