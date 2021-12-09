#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Game;

class Observer {
    public:
    virtual void notify( Game &game ) = 0;
    virtual ~Observer() = default;
};

#endif