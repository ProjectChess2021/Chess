#include "piece.h"
#include "queen.h"
#include <memory>
#include "board.h"
#include "isChecked.h"
#include <iostream>

class Knight;
Posn getKingPosn(const int &side, std::vector<std::vector<Piece *>>& board ) {
    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( board[i][k] && board[i][k]->getType() == 'k') {
                if(  board[i][k]->getSide() == side ) {
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
    //std::cerr << "Starting vertical Check" << std::endl;
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
    //std::cerr << "Starting diagonal Check" << std::endl;
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
                }
            } 
            break;
        }
    }

    return false;
}

bool horizontalChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board ) {
   // std::cerr << "Starting horizontal Check" << std::endl;
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
   // std::cerr << "Starting knight Check" << std::endl;
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
    // std::cerr<<"Check for side="<<side<<std::endl;
    Piece* temp = nullptr;
    std::swap(temp, board[destX][destY]);
    std::swap(board[initX][initY], board[destX][destY]); //move this piece
    bool ans = isChecked( side, board );
    std::swap(board[initX][initY], board[destX][destY]); //move the piece back
    std::swap(temp, board[destX][destY]);
    return ans;
}   // end isCheckMove

// This function returns true if a provided move can put the OTHER side in check
bool IsChecked::canCheckMove(Move& _move, std::vector<std::vector<Piece *>>& _board){
    // DEBUGGING:  unexpected behaviour for FOUR-player!
    int oppID = 3 - _move.getSide();
    int sx = _move.getsx(), sy = _move.getsy(), ex = _move.getex(), ey = _move.getey();
    bool canCheck = false;
    Posn oppKing = getKingPosn(oppID, _board);

    Piece* temp = nullptr;                             // used to store whatever is at the dest
    std::swap(_board[sx][sy], temp);
    std::swap(_board[ex][ey], temp);      // move the direct piece of this move take care of other potential below

    if(_move.getOperation() == "k+p" || _move.getOperation() == "p") {
        //std::cerr << __LINE__ << " " << __FILE__ << " : " << "Check if a promotion can check enemy king" << std::endl;
        Piece* temp2 = _board[ex][ey];                          // before promotion
        std::unique_ptr<Piece> tempQueen = std::make_unique<Queen>(_move.getSide());  // puppet Queen
        _board[ex][ey] = tempQueen.get();
        if(isChecked(oppID, _board))    canCheck = true;
        else {          // check a knight check
            std::unique_ptr<Piece> tempKnight = std::make_unique<Knight>(_move.getSide());  // puppet Knight
            _board[ex][ey] = tempKnight.get();
            if(knightChecked(oppKing.getX(), oppKing.getY(), oppID, _board))    canCheck = true;
        }
        _board[ex][ey] = temp2;                                 // remove the promoted piece
    } else if(_move.getOperation() == "c") {            // a castling can check other side King?
        //std::cerr << __LINE__ << " " << __FILE__ << " : " << "Check if a castling can check enemy king" << std::endl;
        if(ex - _move.getsx() == 2) {                           // from e1/e8 to g1/g8
            // smart_move(_move);                               //DEBUGGING: smart_move?
            // single_undo(_move);
            std::swap(_board[ex - 1][ey],_board[ex + 1][ey]);   // swap rook at h1/h8 to f1/f8
            if(isChecked(oppID, _board))    canCheck = true;
            std::swap(_board[ex - 1][ey],_board[ex + 1][ey]);   // swap rook back
        } else if (ex - _move.getsx() == -2) {                  // from e1/e8 to c1/c8
            // smart_move(_move);                               //DEBUGGING: smart_move?
            // single_undo(_move);
            std::swap(_board['d' - 'a'][ey],_board['a' - 'a'][ey]); // swap rook at a1/a8 to d1/d8
            if(isChecked(oppID, _board))    canCheck = true;
            std::swap(_board['d' - 'a'][ey],_board['a' - 'a'][ey]); // swap rook back
        } else {        // should never goes here
            throw "Wrong Castling Move detected in canCheckMove";
        } 
    } else if (_move.getOperation() == "e") {                   // can en passants check?
        Piece* captured = nullptr;
        std::swap(captured, _move.getSide() == 1 ? _board[ex][ey - 1] : _board[ex][ey + 1]);
        if(captured == nullptr)  throw "En Passant captures nothing in canCheckMove!";
        if(isChecked(oppID, _board))    canCheck =  true;
    } else if (_move.getOperation() == "k" || _move.getOperation() == "m") {
        if(isChecked(oppID, _board))    canCheck =  true;
    } else {
        throw "Unrecognized Move Type in canCheckMove";
    }
    
    // recover last move
    std::swap(_board[ex][ey], temp);
    std::swap(_board[sx][sy], temp);
    return canCheck;
}   // end canCheckMove
