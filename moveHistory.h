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

    void add( const Move &mv );
    Move &undo();

    class MoveHistIter {
        int curr;
        MoveHistIter( const int index );
        public:
        MoveHistIter &operator++();
        Move &operator*();
        bool operator!=(const MoveHistIter&);
        friend class MoveHistory;
    };
    MoveHistIter &begin();
    MoveHistIter &end();
};

#endif
