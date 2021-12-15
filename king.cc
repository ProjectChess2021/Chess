#include "king.h"
#include <vector>
#include <iostream>
#include "isChecked.h"

King::King( const int &side ) : Piece{ side, 'k' } { }

bool King::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffX == 0 && diffY == 0 ) return false;

    if ( -1 <= diffX && diffX <= 1 && -1 <= diffY && diffY <= 1 ) {
        if ( IsChecked::isChecked( endX, endY, getSide(), board ) ) {
            return false;
        }
        if ( board[endX][endY] != nullptr ) {
            return board[endX][endY]->getSide() != getSide();
        }
        return true;
    }
    if ( diffX == 2 && diffY == 0 ) {
        if ( board[7][oriY] == nullptr ) return false;
        for ( int i = oriX + 1; i < 7; ++i ) {
            if ( board[i][oriY] != nullptr ) {
                return false;
            }
        }
        char type = board[7][oriY]->getType();
        if ( !isMoved() && type == 'r' && !board[7][oriY]->isMoved() &&
            board[7][oriY]->getSide() == getSide() ) {
            for ( int x = oriX; x <= endX; ++x ) {
                if ( IsChecked::isChecked( x, oriY, getSide(), board ) ) 
                    return false;
            }
            return true;
        }
    }
    if ( diffX == -2 && diffY == 0 ) {
        if ( board[0][oriY] == nullptr ) return false;
        for ( int i = oriX - 1; i > 0; --i ) {
            if ( board[i][oriY] != nullptr ) {
                return false;
            }
        }
        char type = board[0][oriY]->getType();
        if ( !isMoved() && type == 'r' && !board[0][oriY]->isMoved() &&
            board[0][oriY]->getSide() == getSide() ) {
            for ( int x = oriX; x >= endX; --x ) {
                if ( IsChecked::isChecked( x, oriY, getSide(), board ) ) 
                    return false;
            }
            return true;
        }
    }

    return false;
}

// test case
// int main() {
//     King b = King( 1 );
//     std::vector<std::vector<bool>> display;
//     display.resize( 8, std::vector<bool>( 8, false ) );
//     for ( int i = 0; i < 8; ++i ) {
//         for ( int k = 0; k < 8; ++k ) {
//             Posn p1 = Posn( i, k );
//             for ( int j = 0; j < 8; ++j ) {
//                 for ( int l = 0; l < 8; ++l ) {
//                     display[j][l] = false;
//                 }
//             }
//             for ( int j = 0; j < 8; ++j ) {
//                 for ( int l = 0; l < 8; ++l ) {
//                     Posn p2 = Posn( j, l );
//                     if ( b.isValidMove( &p1, &p2 ) ) {
//                         display[j][l] = true;
//                     }
//                 }
//             }
//             for ( int j = 0; j < 8; ++j ) {
//                 for ( int l = 0; l < 8; ++l ) {
//                     if ( display[j][l] ) {
//                         std::cout << '*';
//                     } else {
//                         std::cout << '-';
//                     }
//                 }
//                 std::cout << std::endl;
//             }
//             std::cout << std::endl;
//         }
//     }
// }
