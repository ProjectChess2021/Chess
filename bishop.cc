#include "bishop.h"
#include <iostream>
#include <vector>

Bishop::Bishop( const int &side ) : Piece{ side, 'b' } { }

bool Bishop::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffY == 0 ) return false;

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
            return board[endX][endY]->getSide() == this->getSide();
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
    }

    return false;
}

// test case
// int main() {
//     Bishop b = Bishop( 1 );
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