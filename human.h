#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Human : public Player {
    public:
    Human( const int &side );
    std::string cmd( Game &game ) override;
};

#endif