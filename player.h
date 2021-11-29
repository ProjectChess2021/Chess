#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player {
    int score;
    int id;
    public:
    int getScore();
    int getId();
    std::string cmd( Board *board );
};

#endif