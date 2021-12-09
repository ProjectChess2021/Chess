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
    bool firstMove;
    std::string operation; //(c)astling,(m)ove,(k)ill,(p)romotion
    public:
    Move(Posn&, Posn&, const int&, const char&, const bool &firstMove);
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const int&, const std::string &operation );
    int getSide() noexcept;
    Posn* getOriginal();
    Posn* getEnd();
    bool isFirstMove();
    std::string getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif