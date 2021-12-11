#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Human : public Player {
    public:
    Human( const int &_id, const int numUndos );
    Human( const int &_id, const int _side, const int numUndos );
    std::string cmd( Game &game ) override;
};

#endif