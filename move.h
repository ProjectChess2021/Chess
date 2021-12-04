// Created By Zichu
// Last Modified At 2121,20211203 (By Kunling Yang)

#ifndef __MOVE_H__ 
#define __MOVE_H__

#include "posn.h"
#include <memory>

class Move {
    std::unique_ptr<Posn> original;
    std::unique_ptr<Posn> end;
    char operation;
    public:
    Move(Posn&, Posn&, const char&) noexcept;
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const char &operation );
    Posn *getOriginal();
    Posn *getEnd();
    char getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif