#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <vector>

class Piece;
class MoveHistory;

class Observer {
    public:
    virtual void notify( std::vector<std::vector<Piece *>> &b, 
        MoveHistory &mh ) = 0;
    virtual ~Observer() = default;
};

#endif
