#include "move.h"

Move::Move( const int &originalX, const int &originalY, const int &finalX, 
    const int &finalY, const char &operation ) : 
    original{ std::make_unique<Posn>( originalX, originalY ) }, 
    end{ std::make_unique<Posn>( finalX, finalY ) },
    operation{ operation } { }

Posn *Move::getOriginal() { return original.get(); }

Posn *Move::getEnd() { return end.get(); }

char Move::getOperation() { return operation; }