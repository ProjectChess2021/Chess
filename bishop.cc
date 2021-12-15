#include "bishop.h"
#include <iostream>
#include <vector>

Bishop::Bishop( const int &side ) : Piece{ side, 'b' } { }

bool Bishop::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffY == 0 || diffX == 0 ) return false;

    if ( diffX == diffY ) {
        if ( diffX > 0 ) {
            for ( int i = 1; i < diffX; ++i  ) {
                if ( board[oriX + i][oriY + i] != nullptr ) return false; 
            }
        } else if ( diffX < 0 ) {
            for ( int i = 1; i < -diffX; ++i  ) {
                if ( board[oriX - i][oriY - i] != nullptr ) return false; 
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    } else if ( diffX == -diffY ) {
        if ( diffX > 0 ) {
            for ( int i = 1; i < diffX; ++i  ) {
                if ( board[oriX + i][oriY - i] != nullptr ) return false; 
            }
        } else if ( diffX < 0 ) {
            for ( int i = 1; i < -diffX; ++i  ) {
                if ( board[oriX - i][oriY + i] != nullptr ) return false; 
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    }

    return false;
}
