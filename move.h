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
    char operation; //(c)astling,(m)ove,(k)ill,(p)romotion
    public:
    Move(Posn&, Posn&, const int&, const char&);
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const int&, const char &operation );
    int getSide() noexcept;
    Posn* getOriginal();
    Posn* getEnd();
    char getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif