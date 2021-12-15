#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

class Observer;
class Piece;
class MoveHistory;

class Subject {
    std::vector<Observer *> obs;
    public:
    void attach( Observer *o );
    void detach( Observer *o );
    void notifyObservers( std::vector<std::vector<Piece *>> &b, 
        MoveHistory &mh );
    virtual ~Subject() = default;
};

#endif
