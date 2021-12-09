#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

class Observer;
class Game;

class Subject {
    std::vector<Observer *> obs;
    public:
    void attach( Observer *o );
    void detach( Observer *o );
    void notifyObservers( Game &game);
    virtual ~Subject() = default;
};

#endif