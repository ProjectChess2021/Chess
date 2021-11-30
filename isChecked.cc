#include <vector>
#include "piece.h"

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