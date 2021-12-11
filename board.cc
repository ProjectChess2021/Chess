#include "board.h"
#include <iostream>
#include "isChecked.h"

Board::Board() {
    board.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    setUpBoard.resize( 8, std::vector<Piece *>( 8, nullptr ) );
}

void Board::boardInit( const bool isSetup ) {
    if ( isSetup ) {
        for ( int i = 0; i < 8; ++i ) {
            for ( int k = 0; k < 8; ++k ) {
                board[i][k] = setUpBoard[i][k];
            }
        }
        return;
    }
    for ( int k = 0; k < 8; ++k ) {
        pieces.emplace_back( std::make_unique<Pawn>( 1 ) );
        board[k][1] = pieces.back().get();
    }
    pieces.emplace_back( std::make_unique<Rook>( 1 ) );
    board[0][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 1 ) );
    board[1][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 1 ) );
    board[2][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Queen>( 1 ) );
    board[3][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<King>( 1 ) );
    board[4][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 1 ) );
    board[5][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 1 ) );
    board[6][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Rook>( 1 ) );
    board[7][0] = pieces.back().get();
    for ( int k = 0; k < 8; ++k ) {
        pieces.emplace_back( std::make_unique<Pawn>( 2 ) );
        board[k][6] = pieces.back().get();
    }
    pieces.emplace_back( std::make_unique<Rook>( 2 ) );
    board[0][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 2 ) );
    board[1][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 2 ) );
    board[2][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Queen>( 2 ) );
    board[3][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<King>( 2 ) );
    board[4][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 2 ) );
    board[5][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 2 ) );
    board[6][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Rook>( 2 ) );
    board[7][7] = pieces.back().get();
}

void Board::move( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    board[endX][endY] = pc;
    board[originalX][originalY] = nullptr;
}

void Board::kill( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];

    deadPool.emplace_back( board[endX][endY] );
    board[originalX][originalY] = nullptr;
    board[endX][endY] = pc;
}

void Board::castle( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    int diffX = endX - originalX;
    if ( diffX == 2 ) {
        board[endX][endY] = pc;
        board[originalX][originalY] = nullptr;
        board[endX - 1][endY] = board[7][endY];
        board[endX - 1][endY]->changeMoved( true );
        board[7][endY] = nullptr; 
    } else {
        board[endX][endY] = pc;
        board[originalX][originalY] = nullptr;
        board[endX + 1][endY] = board[0][endY];
        board[0][endY] = nullptr; 
        board[endX + 1][endY]->changeMoved( true );
    }
}

void Board::promotion( const int &originalX, const int &originalY,
    const int &endX, const int &endY, const char promptTo ) {
    Piece *pc =  board[originalX][originalY];
    if ( promptTo == 'r' ) {
        pieces.emplace_back( std::make_unique<Rook>( pc->getSide() ) );
    } else if ( promptTo == 'n' ) {
        pieces.emplace_back( std::make_unique<Knight>( pc->getSide() ) );
    } else if ( promptTo == 'b' ) {
        pieces.emplace_back( std::make_unique<Bishop>( pc->getSide() ) );
    } else if ( promptTo == 'q' ) {
        pieces.emplace_back( std::make_unique<Queen>( pc->getSide() ) );
    }
    deadPool.emplace_back( pc );
    board[originalX][originalY] = nullptr;
    board[endX][endY] = pieces.back().get();
    pieces.back().get()->changeMoved( true );
}

void Board::killNProm( const int &originalX, const int &originalY, 
    const int &endX, const int &endY, const char promptTo ) {
    kill( originalX, originalY, endX, endY );
    promotion( originalX, originalY, endX, endY, promptTo );
}

void Board::CEP( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    int side = board[originalX][originalY]->getSide();
    board[endX][endY] = pc;
    board[originalX][originalY] = nullptr;
    if ( side == 1 ) {
        deadPool.emplace_back( board[endX][endY - 1] );
        board[endX][endY - 1] = nullptr;
    } else {
        deadPool.emplace_back( board[endX][endY + 1] );
        board[endX][endY + 1] = nullptr;
    }
}

void Board::undo( std::vector<Move *> &undoHist ) {
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
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "c" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( false );
            if ( endX > beginX ) {
                board[7][endY] = board[endX - 1][endY];
                board[7][endY]->changeMoved( false );
                board[endX - 1][endY] = nullptr;
            } else {
                board[0][endY] = board[endX + 1][endY];
                board[0][endY]->changeMoved( false );
                board[endX + 1][endY] = nullptr;
            }
        } else if ( hist->getOperation() == "k" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "k+p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        }
    }
}

std::vector<std::vector<Piece *>> &Board::getBoard() { return board; }

std::vector<std::vector<Piece *>> &Board::getSetUpBoard() { return setUpBoard; }

std::vector<std::unique_ptr<Piece>> &Board::getPieces() { return pieces; };