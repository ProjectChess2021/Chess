#include "piece.h"

Piece::Piece( const int &side, const char &type ) : 
  side{ side }, type{ type }, moved{ false } { }

int Piece::getSide() { return side; }

char Piece::getType() { return type; }

bool Piece::isMoved() { return moved; }

void Piece::changeMoved( bool status ) { moved = status; }

Piece::~Piece() { }
