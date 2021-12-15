// Zichu
// Last Modified At 2259, (UTC-5)20211207 (By Kunling)
#include "move.h"
#include <iomanip>
#include "board.h"
#include <iostream>

std::string findOp( Board &b, Posn &start, Posn &end ) {
    char initType = b.at(start)->getType();
    if(initType == 'k' && std::abs(start.getX() - end.getX()) == 2) { // castling
        return "c";
    } else if (initType == 'p' && (end.getY() == 0 || end.getY() == 7)) { // promotion
        return  (b.at(end) == nullptr) ? "p" : "k+p";   // promotion + kill
    } else if(initType == 'p' && std::abs(end.getX() - start.getX()) == 1 && 
        !b.at(end)) {
        return  "e";    // En passant
    } else if(b.at(end)) {   // there is a piece at dest, thus a caputre
        return  "k";
    } else 
        return  "m";
}

Move::Move(Posn& init, Posn& dest, const int& _side, const std::string& op, 
    const bool &_isFirstMove) :
    original{ std::make_unique<Posn>(init) },
    end{ std::make_unique<Posn>(dest) },
    side{_side},
    firstMove{_isFirstMove},
    operation{op} {}    // end Constructor

Move::Move( const int &initX, const int &initY, const int &destX, 
    const int &destY, const int _side, const std::string operation, 
    bool _isFirstMove) : 
    original{ std::make_unique<Posn>( initX, initY ) },
    end{ std::make_unique<Posn>( destX, destY ) },
    side{_side},
    firstMove{_isFirstMove},
    operation{ operation } { } // end Constructor

Move::Move(Board& _board, Posn& init, Posn& dest) : 
    original{ std::make_unique<Posn>(init) },
    end{ std::make_unique<Posn>(dest) },
    side{_board.at(init)->getSide()},
    firstMove{_board.at(init)->isMoved()}, 
    operation{ findOp( _board, init, dest ) } {
    
}   // end Constructor

Move::Move(Board& _board, const int sx, const int sy, const int ex, const int ey) :
    original{ std::make_unique<Posn>( sx, sy ) },
    end{ std::make_unique<Posn>( ex, ey ) },
    side{ _board.at( sx, sy )->getSide() },
    firstMove{ !_board.at( sx, sy )->isMoved() },
    operation{ findOp( _board, *original, *end ) } { 
   // std::cerr << "Finished move" << std::endl; 
}   // end Constructor

int Move::getSide() {return side;}

Posn *Move::getOriginal() { return original.get(); }

Posn *Move::getEnd() { return end.get(); }

bool Move::isFirstMove() { return firstMove; }

std::string Move::getOperation() { return operation; }

int Move::getsx() {return original.get()->getX();}
int Move::getsy() {return original.get()->getY();}
int Move::getex() {return end.get()->getX();}
int Move::getey() {return end.get()->getY();}

// This function translates the peice type character to a string
std::string getTypeStr(const char c) {
    if(toupper(c) == 'P')    return "pawn";
    else if(toupper(c) == 'R')  return "rook";
    else if(toupper(c) == 'N')  return "knight";
    else if(toupper(c) == 'B')  return "bishop";
    else if(toupper(c) == 'Q')  return "queen";
    else if(toupper(c) == 'K')  return "king";
    else return "";
}   // end getTypeStr

std::ostream &operator<<( std::ostream & out, const Move& _move){
    out << *_move.original << " -> " << *_move.end;
    return out;
}   // end operator<<
