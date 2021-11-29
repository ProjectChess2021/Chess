#include "king.h"
#include <vector>
#include <iostream>

King::King( const int &side ) : Piece{ side, 'k' } { }

bool verticalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    for ( int i = 1; y + i < 8; ++i ) {
        if ( board[x][y + i] != nullptr ) {
            char type = board[x][y + i]->getType();
            int otherSide = board[x][y + i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'r' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            }
            break;
        }
    }

    for ( int i = 1; y - i >= 0; ++i ) {
        if ( board[x][y - i] != nullptr ) {
            char type = board[x][y - i]->getType();
            int otherSide = board[x][y - i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'r' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            }
            break;
        }
    }

    return false;
}

bool diagonalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    for ( int i = 1; y + i < 8 && x + i < 8; ++i ) {
        if ( board[x + i][y + i] != nullptr ) {
            char type = board[x + i][y + i]->getType();
            int otherSide = board[x + i][y + i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'b' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            } 
            break;
        }
    }

    for ( int i = 1; y - i >= 0 && x + i < 8; ++i ) {
        if ( board[x + i][y - i] != nullptr ) {
            char type = board[x + i][y - i]->getType();
            int otherSide = board[x + i][y - i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'b' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            } 
            break;
        }
    }

    for ( int i = 1; y + i < 8 && x - i >= 0; ++i ) {
        if ( board[x - i][y + i] != nullptr ) {
            char type = board[x - i][y + i]->getType();
            int otherSide = board[x - i][y + i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'b' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            } 
            break;
        }
    }

    for ( int i = 1; y - i >= 0 && x - i >= 0; ++i ) {
        if ( board[x - i][y - i] != nullptr ) {
            char type = board[x - i][y - i]->getType();
            int otherSide = board[x - i][y - i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'b' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            } 
            break;
        }
    }

    return false;
}

bool horizontalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    for ( int i = 1; x + i < 8; ++i ) {
        if ( board[x + i][y] != nullptr ) {
            char type = board[x + i][y]->getType();
            int otherSide = board[x + i][y]->getSide();
            if ( otherSide != side ) {
                if ( type == 'r' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            }
            break;
        }
    }

    for ( int i = 1; x - i >= 0; ++i ) {
        if ( board[x - i][y] != nullptr ) {
            char type = board[x - i][y]->getType();
            int otherSide = board[x - i][y]->getSide();
            if ( otherSide != side ) {
                if ( type == 'r' || type == 'q' ) {
                    return true;
                }   
                if ( type == 'k' && i == 1 ) {
                    return true;
                }
            }
            break;
        }
    }
}

bool knightChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    std::vector<int> arr;
    arr.emplace_back( 1 );
    arr.emplace_back( 2 );
    arr.emplace_back( -1 );
    arr.emplace_back( -2 );
    for ( auto i : arr ) {
        for ( auto k : arr ) {
            if ( abs( i ) != abs( k ) ) {
                if ( board[x + i][y + k] != nullptr ) {
                char type = board[x + i][y + k]->getType();
                int otherSide = board[x + i][y + k]->getSide();
                if ( otherSide != side ) {
                    if ( type == 'n' ) return true;
                }
            }
            }
        }
    }
}

bool isChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    
    // Vertical check
    if ( verticalChecked( x, y, side, board ) ) return true;

    // Diagnal check
    if ( diagonalChecked( x, y, side, board ) ) return true;

    // Horizontal checked
    if ( horizontalChecked( x, y, side, board ) ) return true;

    // Knight checked
    if ( knightChecked( x, y, side, board ) ) return true;

    return false;
}

bool King::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffX == 0 && diffY == 0 ) return false;

    if ( -1 <= diffX && diffX <= 1 && -1 <= diffY && diffY <= 1 ) {
        if ( isChecked( endX, endY, getSide(), board ) ) {
            return false;
        }
        if ( board[endX][endY] != nullptr ) {
            if ( board[endX][endY] != nullptr ) {
                return board[endX][endY]->getSide() == this->getSide();
            }
        }
    }
        

    if ( diffX == 2 && diffY == 0 && ( oriY == 0 || oriY == 8 ) ) {
        for ( int i = oriX; i < 7; ++i ) {
            if ( board[i][oriY] != nullptr ) {
                return false;
            }
        }
        char type = board[7][oriY]->getType();
        if ( !isMoved() && type == 'r' && !board[7][oriY]->isMoved() ) {
            for ( int x = oriX; x <= endX; ++x ) {
                if ( isChecked( x, oriY, getSide(), board ) ) return false;
            }
            return true;
        }
    }
    else if ( diffX == -2 && diffY == 0 && ( oriY == 0 || oriY == 8 ) ) {
        for ( int i = oriX; i > 0; --i ) {
            if ( board[i][oriY] != nullptr ) {
                return false;
            }
        }
        char type = board[0][oriY]->getType();
        if ( !isMoved() && type == 'r' && !board[0][oriY]->isMoved() ) {
            for ( int x = oriX; x >= endX; --x ) {
                if ( isChecked( x, oriY, getSide(), board ) ) return false;
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