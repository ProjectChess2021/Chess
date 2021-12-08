// Zichu
// Last Modified At 2259, (UTC-5)20211207 (By Kunling)
#include "move.h"
#include <iomanip>

Move::Move(Posn& init, Posn& dest, const int& _side, const char& op) :
    original{std::make_unique<Posn>(init)},
    end{std::make_unique<Posn>(dest)},
    side{_side},
    operation{op}   {}

Move::Move( const int &originalX, const int &originalY, const int &finalX, 
    const int &finalY, const int& _side, const char &operation ) : 
    original{ std::make_unique<Posn>( originalX, originalY ) }, 
    end{ std::make_unique<Posn>( finalX, finalY ) },
    side{_side},
    operation{ operation } { }

int Move::getSide() {return side;}

Posn *Move::getOriginal() { return original.get(); }

Posn *Move::getEnd() { return end.get(); }

char Move::getOperation() { return operation; }

// This function translates the side number to a string (colour representing the player)
std::string getSideStr(const int x){
    std::cerr << "translate side to string @ Line 25, move.cc" << std::endl;
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
    std::cerr << "Printing out a move info @ Line 44, move.cc" << std::endl;
    std::string sideStr = getSideStr(_move.side);
    sideStr[0] = toupper(sideStr[0]);
    // out << sideStr << ":" << std::right << std::setw(6) << getTypeStr(_move.operation) << " ";
    // out << *_move.original << " -> " << *_move.end;
    out << sideStr << ": " << *_move.original << " -> " << *_move.end;
    return out;
}   // end operator<<
