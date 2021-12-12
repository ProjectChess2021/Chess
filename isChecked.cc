#include "piece.h"
#include "isChecked.h"
#include <iostream>

Posn getKingPosn(const int &side, std::vector<std::vector<Piece *>>& board ) {
    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( board[i][k] && board[i][k]->getType() == 'k') {
                std::cerr <<  "Side = " << board[i][k]->getSide()  << "and curr side is " <<side << std::endl;
                if(  board[i][k]->getSide() == side ) {
                    std::cerr<< "retrieved successful" << std::endl;
                    Posn ret{i,k};
                    return ret;
                }
            }
        }
    }
    std::cerr << "Error! King not found at " << __LINE__ << " in " << __FILE__  <<std::endl;
    Posn ret{0,0};
    return ret;
}   // end getKingPosn

bool verticalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    std::cerr << "Starting vertical Check" << std::endl;
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
    std::cerr << "Starting diagonal Check" << std::endl;
    for ( int i = 1; y + i < 8 && x + i < 8; ++i ) {
        if ( board[x + i][y + i] != nullptr ) {
            char type = board[x + i][y + i]->getType();
            int otherSide = board[x + i][y + i]->getSide();
            if ( otherSide != side ) {
                if ( type == 'b' || type == 'q' ) {
                    return true;
                }   
                if (i == 1 ) {
                    if(type == 'k') return true;
                    else if(type == 'p' && otherSide == 2)  // black pawn attack white king
                        return true;                        // from [x+1][y+1]
                    std::cerr << __LINE__ << std::endl;
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
                if (i == 1 ) {
                    if(type == 'k') return true;
                    else if(type == 'p' && otherSide == 1)  // white pawn attack black king
                        return true;                        // from [x+1][y-1]
                    std::cerr << __LINE__ << std::endl;
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
                if (i == 1 ) {
                    if(type == 'k') return true;
                    else if(type == 'p' && otherSide == 2)  // black pawn attack white king
                        return true;                        // from [x-1][y+1]
                    std::cerr << __LINE__ << std::endl;
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
                if (i == 1 ) {
                    if(type == 'k') return true;
                    else if(type == 'p' && otherSide == 1)  // white pawn attack black king
                        return true;                        // from [x-1][y-1]
                    std::cerr << __LINE__ << std::endl;
                }
            } 
            break;
        }
    }

    return false;
}

bool horizontalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    std::cerr << "Starting horizontal Check" << std::endl;
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

    return false;
}

bool knightChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
    std::cerr << "Starting knight Check" << std::endl;
    std::vector<int> arr;
    arr.emplace_back( 1 );
    arr.emplace_back( 2 );
    arr.emplace_back( -1 );
    arr.emplace_back( -2 );
    for ( auto i : arr ) {
        for ( auto k : arr ) {
            if ( abs( i ) != abs( k ) ) {
                if ( x + i >= 8 || x + i < 0 || y + k >= 8 || y + k < 0 ) {
                    continue;
                }
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

    return false;
}

bool IsChecked::isChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>>& board ) {

    Piece *pc = nullptr;
    int kingX = 0;
    int kingY = 0;

    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( board[i][k] ) {
                if ( board[i][k]->getType() == 'k' && 
                     board[i][k]->getSide() == side ) {
                    kingX = i;
                    kingY = k;
                }
            }
        }
    }

    std::cerr << std::endl;
    std::cerr << "The King for side = " << side << " is at " << kingX << kingY << std::endl;
    std::cerr << std::endl;
    
    std::swap( board[kingX][kingY], pc );

    // Vertical check
    if ( verticalChecked( x, y, side, board ) ) {
        std::swap( board[kingX][kingY], pc );
        return true;
    }

    // Diagnal check
    if ( diagonalChecked( x, y, side, board ) ) {
        std::swap( board[kingX][kingY], pc );
        return true;
    }
    // Horizontal checked
    if ( horizontalChecked( x, y, side, board ) ) {
        std::swap( board[kingX][kingY], pc );
        return true;
    }
    // Knight checked
    if ( knightChecked( x, y, side, board ) ) {
        std::swap( board[kingX][kingY], pc );
        return true;
    }

    std::swap( board[kingX][kingY], pc );

    return false;
}

bool IsChecked::isChecked( const int &side,
    std::vector<std::vector<Piece *>>& board ) {
    int kingX = 0;
    int kingY = 0;
    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( board[i][k] ) {
                if ( board[i][k]->getType() == 'k' && 
                     board[i][k]->getSide() == side ) {
                    kingX = i;
                    kingY = k;
                    i = 8;
                    k = 8;
                }
            }
        }
    }
    return isChecked( kingX, kingY, side, board );
}

// This function returns true if a move from (initX,initY) to (destX,destY) causes player being checked.
// Noticed that board is passed by value thus can be safely modifed without affecting the true board
bool IsChecked::isCheckMove(const int initX, const int initY, const int destX, const int destY,
    const int side, std::vector<std::vector<Piece *>>& board) {
        std::cerr<<"Check for side="<<side<<std::endl;
    Piece* temp = nullptr;
    std::swap(temp, board[destX][destY]);
    std::swap(board[initX][initY], board[destX][destY]); //move this piece
    bool ans = isChecked( side, board );
    std::swap(board[initX][initY], board[destX][destY]); //move the piece back
    std::swap(temp, board[destX][destY]);
    return ans;
}   // end isCheckMove