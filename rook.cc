#include "rook.h"
#include <vector>

Rook::Rook( const int &side ) : Piece{ side, 'r' } { }

bool Rook::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffY == 0 && diffX == 0 ) return false;

    // Moving vertically
    if ( diffX == 0 ) {
        if ( diffY > 0 ) {
            for ( int y = oriY + 1; y < endY; ++y ) {
                if ( board[oriX][y] != nullptr ) return false;
            }
        }
        if ( diffY < 0 ) {
            for ( int y = oriY - 1; y > endY; --y ) {
                if ( board[oriX][y] != nullptr ) return false;
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    }

    // Moving Horizontally
    if ( diffY == 0 ) {
        if ( diffX > 0 ) {
            for ( int x = oriX + 1; x < endX; ++x ) {
                if ( board[x][oriY] != nullptr ) return false;
            }
        }
        if ( diffX < 0 ) {
            for ( int x = oriX - 1; x > endX; --x ) {
                if ( board[x][oriY] != nullptr ) return false;
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    }

    return false;
}
