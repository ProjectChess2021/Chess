// Zichu
// Last Modified At 2259, (UTC-5)20211207 (By Kunling)
#include "move.h"
#include <iomanip>
#include "board.h"
#include <iostream>

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
    firstMove{_board.at(init)->isMoved()} {
        char initType = _board.at(init)->getType();
    if(initType == 'k' && std::abs(init.getX() - dest.getX()) == 2) { // castling
        operation = "c";
    } else if (initType == 'p' && (dest.getY() == 0 || dest.getY() == 7)) { // promotion
        operation = (_board.at(dest) == nullptr) ? "p" : "k+p";   // promotion + kill
    }  else if(initType == 'p' && std::abs(dest.getX() - init.getX()) == 1 && !_board.at(dest)) {
        operation = "e";    // En passant
    }
    else if(_board.at(dest)) {   // there is a piece at dest, thus a caputre
        operation = "k";
    } else operation = "m";
}   // end Constructor

Move::Move(Board& _board, const int sx, const int sy, const int ex, const int ey) {
    Posn st{sx,sy};
    Posn ed{ex,ey};
    Move(_board, st, ed);
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

// This function translates the side number to a string (colour representing the player)
std::string getSideStr(const int x){
    if(x == 1)     return "white";
    else if(x == 2) return "black";
    else if(x == 3) return "azure";
    else if(x == 4) return "green";
    else return "";
}   // end getSideStr

// This function translates the peice type character to a string
std::string getTypeStr(const char c) {
    std::cerr << "translate type to string @ Line34, move.cc" << std::endl;
    if(toupper(c) == 'P')    return "pawn";
    else if(toupper(c) == 'R')  return "rook";
    else if(toupper(c) == 'N')  return "knight";
    else if(toupper(c) == 'B')  return "bishop";
    else if(toupper(c) == 'Q')  return "queen";
    else if(toupper(c) == 'K')  return "king";
    else return "";
}   // end getTypeStr

std::ostream &operator<<( std::ostream & out, const Move& _move){
    std::string sideStr = getSideStr(_move.side);
    sideStr[0] = toupper(sideStr[0]);
    // out << sideStr << ":" << std::right << std::setw(6) << getTypeStr(_move.operation) << " ";
    // out << *_move.original << " -> " << *_move.end;
    out << sideStr << ": " << *_move.original << " -> " << *_move.end;
    return out;
}   // end operator<<
