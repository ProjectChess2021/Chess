// Created By Zichu
// Last Modifed At 0005, 20211201 (By Kunling)
#ifndef __MOVEHISTORY_H__
#define __MOVEHISTORY_H__

#include "move.h"
#include <vector>
#include <memory>

class MoveHistory {
    std::vector<std::unique_ptr<Move>> mh;

    public:
    MoveHistory();

    void add( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, Board &b );
    std::vector<Move *> undo();

    Move *lastMove();
    bool hasMoved();

    void clearHistory();
    int size();
    class MoveHistIter {
        int curr;
        std::vector<std::unique_ptr<Move>> &mh;
        MoveHistIter( const int &index, 
            std::vector<std::unique_ptr<Move>> &mh );
        public:
        MoveHistIter &operator++();
        MoveHistIter &operator--();
        Move &operator*();
        bool operator!=(const MoveHistIter&);
        friend class MoveHistory;
    };
    MoveHistIter begin();
    MoveHistIter end();
};

#endif
