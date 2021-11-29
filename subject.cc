#include "subject.h"
#include "observer.h"

void Subject::attach( Observer *o ) { obs.emplace_back( o ); }

void Subject::detach( Observer *o ) { 
    for (auto it = obs.begin(); it != obs.end(); ) {
        if (*it == o) it = obs.erase(it);
        else ++it;
    }
}

void Subject::notifyObservers() {
    for ( auto &ob : obs ) {
        ob->notify();
    }
}