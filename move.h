// Zichu
// Last Modified At (UTC-5)2244,20211207 (By Kunling)

#ifndef __MOVE_H__ 
#define __MOVE_H__

#include "posn.h"
#include <memory>

class Move {
    std::unique_ptr<Posn> original;
    std::unique_ptr<Posn> end;
    int side;
    char type;
    char operation;
    public:
    Move(Posn&, Posn&, const char&);
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const char &operation );
    Posn* getOriginal();
    Posn* getEnd();
    char getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif