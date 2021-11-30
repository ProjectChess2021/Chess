#ifndef __BOT_H__
#define __BOT_H__

#include "player.h"

class Bot : public Player {
    public:
    Bot( const int &side );
    std::string cmd( std::vector<std::vector<Piece *>> board ) override;
};

#endif