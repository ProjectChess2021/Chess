#ifndef __MOVEHISTORY_H__
#define __MOVEHISTORY_H__

#include "move.h"

class MoveHistory : public Subject {
    int maxUndos;
    std::vector<std::unique_ptr<Move>> mh;

    public:
    MoveHistory( const int &maxUndo );

    void add( const Move &mv );
    Move &undo();

    class MoveHistIter {
        int index;
        MoveHistIter( const int index );
        public:
        MoveHistIter &begin();
        MoveHistIter &end();
        MoveHistIter &operator++();
        Move &operator*();
    }
};

#endif