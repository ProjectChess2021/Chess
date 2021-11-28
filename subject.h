#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

class Observer;

class Subject {
    std::vector<Observer *> obs;
    public:
    void attach( Observer *o );
    void detach(Observer *o);
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif