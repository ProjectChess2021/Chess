// Zichu
// Last Modified At (UTC-5)2254,20211209 (By Kunling)

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
    Move(Posn&, Posn&, const int&, const std::string&, const bool &firstMove);
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const int&, const std::string &operation, const bool& );
    int getSide();
    Posn* getOriginal();
    Posn* getEnd();
    bool isFirstMove();
    std::string getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif