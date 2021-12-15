#include "queen.h"
#include <vector>
#include <iostream>

Queen::Queen( const int &side ) : Piece{ side, 'q' } { }

bool Queen::isValidMove( Posn *original, Posn *end, 
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
                if ( board[oriX][y] != nullptr ) {
                    if ( board[oriX][y]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( diffY < 0 ) {
            for ( int y = oriY - 1; y > endY; --y ) {
                if ( board[oriX][y] != nullptr ) {
                    if ( board[oriX][y]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != getSide();
        return true;
    }

    // Moving Horizontally
    if ( diffY == 0 ) {
        if ( diffX > 0 ) {
            for ( int x = oriX + 1; x < endX; ++x ) {
                if ( board[x][oriY] != nullptr ) {
                    if ( board[x][oriY]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( diffX < 0 ) {
            for ( int x = oriX - 1; x > endX; --x ) {
                if ( board[x][oriY] != nullptr ) {
                    if ( board[x][oriY]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != getSide();
        return true;
    }

    // Moving diagonally
    if ( diffX == diffY ) {
        if ( diffX > 0 ) {
            for ( int i = 1; i < diffX; ++i  ) {
                if ( board[oriX + i][oriY + i] != nullptr ) {
                    if ( board[oriX + i][oriY + i]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        } else if ( diffX < 0 ) {
            for ( int i = 1; i < -diffX; ++i  ) {
                if ( board[oriX - i][oriY - i] != nullptr ) {
                    if ( board[oriX - i][oriY - i]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    } 
    
    if ( diffX == -diffY ) {
        if ( diffX > 0 ) {
            for ( int i = 1; i < diffX; ++i  ) {
                if ( board[oriX + i][oriY - i] != nullptr ) {
                    if ( board[oriX + i][oriY - i]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        } else if ( diffX < 0 ) {
            for ( int i = 1; i < -diffX; ++i  ) {
                if ( board[oriX - i][oriY + i] != nullptr ) {
                    if ( board[oriX - i][oriY + i]->getSide() == getSide() ) {
                        return false;
                    }
                }
            }
        }
        if ( board[endX][endY] != nullptr ) 
            return board[endX][endY]->getSide() != this->getSide();
        return true;
    }

    return false;
}
