#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Human : public Player {
    std::string valid( const int &iniX, const int &iniY, const int &endX, 
    const int &endY, Game &g );
    public:
    Human( const int &_id, const float score = 0 );
    std::string cmd( Game &game ) override;
    char promptTo() override;
};

#endif
