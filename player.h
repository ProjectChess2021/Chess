#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "player.h"

class Player {
    int score;
    int id;
    public:
    int getScore();
    int getId();
    std::string cmd( std::vector<std::vector<Piece *>> board );
};

#endif