// Created By Zichu
// Last Modifed At 0005, 20211201 (By Kunling)
#ifndef __MOVEHISTORY_H__
#define __MOVEHISTORY_H__

#include "move.h"
#include <vector>
#include <memory>

class MoveHistory {
    int maxUndos;
    std::vector<std::unique_ptr<Move>> mh;

    public:
    MoveHistory( const int &maxUndo );

    void add( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const char &operation );
    std::vector<Move *> undo();

    void clearHistory();

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
