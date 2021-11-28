#ifndef __MOVE_H__ 
#define __MOVE_H__

#include "Posn.h"

class Move {
    std::unique_ptr<Posn> original;
    std::unique_ptr<Posn> end;
    char operation;
    public:
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalX, const char &operation );
    Posn *getOriginal();
    Posn *getEnd();
};

#endif