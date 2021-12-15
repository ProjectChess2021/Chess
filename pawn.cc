#include "pawn.h"
#include <iostream>
#include <vector>

Pawn::Pawn( const int &side ) : Piece{ side, 'p' } { }

bool Pawn::isValidMove( Posn *original, Posn *end, 
    std::vector<std::vector<Piece *>> &board, MoveHistory *mh ) {
    int oriX = original->getX();
    int oriY = original->getY();
    int endX = end->getX();
    int endY = end->getY();
    int diffX = endX - oriX;
    int diffY = endY - oriY;

    if ( diffY == 0 && diffX == 0 ) return false;

    if ( diffX == 0 ) {
        if ( getSide() == 1 ) {
            if ( diffY == 1 ) {
                if ( board[endX][endY] != nullptr ) 
                    return false;;
                return true;
            }
            if ( diffY == 2 ) {
                if ( !isMoved() ) {
                    if ( board[endX][endY] != nullptr || 
                         board[endX][endY - 1] != nullptr ) 
                        return false;
                    return true;
                }
            }
        }
        if ( getSide() == 2 ) {
            if ( diffY == -1 ) {
                if ( board[endX][endY] != nullptr ) 
                    return false;
                return true;
            }
            if ( diffY == -2 ) {
                if ( !isMoved() ) {
                    if ( board[endX][endY] != nullptr || 
                         board[endX][endY + 1] != nullptr ) 
                        return false;
                    return true;
                }
            }
        }
    }

    if ( ( diffX == 1 || diffX == -1 ) ) {
        if ( diffY == 1 && getSide() == 1 ) {
            if ( board[endX][endY] != nullptr ) {
                if ( board[endX][endY]->getSide() != getSide() ) {
                    return true;
                }
            }
        }
        if ( diffY == -1 && getSide() == 2 ) {
            if ( board[endX][endY] != nullptr ) {
                if ( board[endX][endY]->getSide() != getSide() ) {
                    return true;
                }
            }
        }
    }

    if ( mh->hasMoved() ) {
        Move *lastMove = mh->lastMove();
        Posn *lastMoveEnd = lastMove->getEnd();
        Posn *lastMoveBegin = lastMove->getOriginal();
        Piece *lastPiece = board[lastMoveEnd->getX()][lastMoveEnd->getY()];
        if ( lastPiece->getType() == 'p' ) {
            if ( ( diffX == 1 || diffX == -1 ) ) {
                if ( diffY == 1 && getSide() == 1 ) {
                    if ( endX == lastMoveEnd->getX() && 
                        endY - 1 == lastMoveEnd->getY() &&
                        endX == lastMoveBegin->getX() && 
                        endY + 1 == lastMoveBegin->getY() &&
                        lastPiece->getSide() != getSide() ) {
                        return true;
                    }
                }
            }
            if ( diffY == -1 && getSide() == 2 ) {
                if ( board[endX][endY + 1] != nullptr ) {
                    if ( endX == lastMoveEnd->getX() && 
                        endY + 1 == lastMoveEnd->getY() &&
                        endX == lastMoveBegin->getX() && 
                        endY - 1 == lastMoveBegin->getY() &&
                        lastPiece->getSide() != getSide() ) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
