#include "game.h"

Game::Game( std::vector<Player *> &players ) : players{ players } { }

std::string Game::move( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    int side = board[originalX][originalY]->getSide();
    std::string retval = "";

    // The case when piece is going to kill another piece
    if ( board[endX][endY] != nullptr ) {
        deadPool.emplace_back( board[endX][endY] );
        board[originalX][originalY] = nullptr;
        board[endX][endY] = pc;
        retval = "k";
    }

    // Checking pawn capture en passant
    

    if ( pc->getType() == 'p' && mh->hasMoved() ) {
        Move *lastMove = mh->lastMove();
        Posn *lastMoveEnd = lastMove->getEnd();
        Posn *lastMoveBegin = lastMove->getOriginal();
        Piece *lastPiece = board[lastMoveEnd->getX()][lastMoveEnd->getY()];
        if ( lastPiece->getType() == 'p' ) {
            if ( side == 1 ) {
                if ( endX == lastMoveEnd->getX() && 
                     endY - 1 == lastMoveEnd->getY() &&
                     endX == lastMoveBegin->getX() && 
                     endY + 1 == lastMoveBegin->getY() &&
                     lastPiece->getSide() != pc->getSide() ) {
                    retval = "k";
                }
            } else if ( side == 2 ) {
                if ( endX == lastMoveEnd->getX() && 
                     endY + 1 == lastMoveEnd->getY() &&
                     endX == lastMoveBegin->getX() && 
                     endY - 1 == lastMoveBegin->getY() &&
                     lastPiece->getSide() != pc->getSide() ) {
                    retval = "k";
                }
            }
        }
    }

    // Now checking if this is a promotion
    if ( pc->getType() == 'p' ) {
        if ( endY == 7 || endY == 0 ) {
            char promptTo = 'a';
            while ( true ) {
                std::cout << "Your pawn is being granted a promotion" << std::endl;
                std::cout << "You can change your pawn into:" << std::endl;
                std::cout << "(r)ook" << std::endl;
                std::cout << "(k)night" << std::endl;
                std::cout << "(b)ishop" << std::endl;
                std::cout << "(q)ueen" << std::endl;
                std::cin >> promptTo;
                if ( promptTo == 'r' ) {
                    pieces.emplace_back( std::make_unique<Rook>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'k' ) {
                    pieces.emplace_back( std::make_unique<Knight>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'b' ) {
                    pieces.emplace_back( std::make_unique<Bishop>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'q' ) {
                    pieces.emplace_back( std::make_unique<Queen>( pc->getSide() ) );
                    break;
                }
            }
            deadPool.emplace_back( pc );
            board[endX][endY] = pieces.back().get();
            pieces.back().get()->isMoved() = true;
            if ( retval == "k" ) {
                retval += "+p";
            } else {
                retval = "p";
            }
        }
    }

    // Now check for castling
    if ( pc->getType() == 'k' ) {
        int diffX = endX - originalX;
        if ( diffX == 2 || diffX == -2 ) {
            if ( diffX == 2 ) {
                board[endX][endY] = pc;
                board[originalX][originalY] = nullptr;
                board[endX - 1][endY] = board[7][endY];
                board[endX - 1][endY]->isMoved() = true;
                board[7][endY] = nullptr; 
            } else {
                board[endX][endY] = pc;
                board[originalX][originalY] = nullptr;
                board[endX + 1][endY] = board[0][endY];
                board[0][endY] = nullptr; 
                board[endX + 1][endY]->isMoved() = true;
            }
            retval = "c";
        }
    }

    return retval;
}

void Game::undo() {
    std::vector<Move *> undoHist = mh->undo();
    for ( auto hist : undoHist ) {
        Posn *end = hist->getEnd();
        Posn *begin = hist->getOriginal();
        int endX = end->getX();
        int endY = end->getY();
        int beginX = begin->getX();
        int beginY = begin->getY();
        if ( hist->getOperation() == "m" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->isMoved() = hist->isFirstMove();
        } else if ( hist->getOperation() == "c" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->isMoved() = hist->isFirstMove();
        }
    }
}