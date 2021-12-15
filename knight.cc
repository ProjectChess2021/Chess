#include "knight.h"
#include <iostream>
#include <vector>

Knight::Knight( const int &side ) : Piece{ side, 'n' } { }

bool Knight::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( ( diffX == 2 || diffX == -2 ) && ( diffY == 1 || diffY == -1 ) ) {
        if ( board[endX][endY] != nullptr ) {
            if ( board[endX][endY]->getSide() == getSide() ) {
                return false;
            }
        }
        return true;
    }
    if ( ( diffX == 1 || diffX == -1 ) && ( diffY == 2 || diffY == -2 ) ) {
        if ( board[endX][endY] != nullptr ) {
            if ( board[endX][endY]->getSide() == getSide() ) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// test case
// int main() {
//     Knight b = Knight( 1 );
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
