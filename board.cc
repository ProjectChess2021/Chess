#include "board.h"
#include <iostream>
#include "move.h"
#include "isChecked.h"
using std::vector;
class Posn;

Board::Board() {
    board.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    setUpBoard.resize( 8, std::vector<Piece *>( 8, nullptr ) );
}

void Board::boardInit( const bool isSetup ) {
    if ( isSetup ) {
        for ( int i = 0; i < 8; ++i ) {
            for ( int k = 0; k < 8; ++k ) {
                board[i][k] = setUpBoard[i][k];
                if ( board[i][k] )
                    board[i][k]->changeMoved( false );
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
    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            setUpBoard[i][k] = board[i][k];
            if ( board[i][k] )
                board[i][k]->changeMoved( false );
        }
    }
}

void move(vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
     const int &originalX, const int &originalY, const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    board[endX][endY] = pc;
    board[originalX][originalY] = nullptr;
}

void kill( vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
    const int &originalX, const int &originalY, const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];

    deadPool.emplace_back( board[endX][endY] );
    board[originalX][originalY] = nullptr;
    board[endX][endY] = pc;
}

void castle(vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
     const int &originalX, const int &originalY, 
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

void promotion( vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
    const int &endX, const int &endY, const char promptTo ) {
    Piece *pc =  board[endX][endY];
    if ( promptTo == 'r' ) {
        pieces.emplace_back( std::make_unique<Rook>( pc->getSide() ) );
    } else if ( promptTo == 'n' ) {
        pieces.emplace_back( std::make_unique<Knight>( pc->getSide() ) );
    } else if ( promptTo == 'b' ) {
        pieces.emplace_back( std::make_unique<Bishop>( pc->getSide() ) );
    } else if ( promptTo == 'q' ) {
        pieces.emplace_back( std::make_unique<Queen>( pc->getSide() ) );
    }
    deadPool.emplace_back( board[endX][endY] );
    board[endX][endY] = pieces.back().get();
    pieces.back().get()->changeMoved( true );
}

void moveNProm( vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
    const int &originalX, const int &originalY, 
    const int &endX, const int &endY, const char promptTo ) {
    move( pieces, board, deadPool,originalX, originalY, endX, endY );
    promotion( pieces, board, deadPool,endX, endY, promptTo );
}

void killNProm(vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
     const int &originalX, const int &originalY, 
    const int &endX, const int &endY, const char promptTo ) {
    kill( pieces, board, deadPool,originalX, originalY, endX, endY );
    promotion( pieces, board, deadPool,endX, endY, promptTo );
}

void CEP(vector<std::unique_ptr<Piece>>& pieces, vector<vector<Piece *>>& board, vector<Piece *> &deadPool,
     const int &originalX, const int &originalY, 
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

void Board::smart_move(Move& _move, const char promptTo) {
    int sx = _move.getsx();
    int sy = _move.getsy();
    int ex = _move.getex();
    int ey = _move.getey();
    Piece *pc = board[sx][sy];
    std::string op = _move.getOperation();
    if(board[sx][sy] == nullptr)    throw "Initial Position has no piece!";
    if(board[ex][ey] == nullptr && (op == "k" || op == "k+p"))     
        throw "Kill Or KnP has no Piece at dest";
    if(board[ex][ey] != nullptr && (op == "c" || op == "m" || op == "e"))
        throw "Castling or Move has Piece at dest";
    if (_move.getOperation() == "k")        kill(pieces, board, deadPool,sx, sy, ex, ey);
    else if(_move.getOperation() == "c")    castle(pieces, board, deadPool, sx, sy, ex, ey);
    else if(_move.getOperation() == "p")    moveNProm(pieces, board, deadPool, sx, sy, ex, ey, promptTo );
    else if(_move.getOperation() == "k+p")  killNProm(pieces, board, deadPool,sx, sy, ex, ey, promptTo );
    else if(_move.getOperation() == "e")    CEP(pieces, board, deadPool,sx, sy, ex, ey);
    else move(pieces, board, deadPool,sx, sy, ex, ey);

    pc->changeMoved(true);
}   // end smart_move

// This function undos a single move in convinience of bot
void Board::undo(Move* _move) {
    std::vector<Move*> undoLst;
    undoLst.emplace_back(_move);
    undo(undoLst);
}   // end undo

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
            board[beginX][beginY]->changeMoved( !hist->isFirstMove() );
        } else if ( hist->getOperation() == "c" ) {     // undo castling
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( false );
            if ( endX > beginX ) {                      // king: e1/e8 -> h1/h8
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
            board[beginX][beginY]->changeMoved( !hist->isFirstMove() );
        } else if ( hist->getOperation() == "p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( !hist->isFirstMove() );
        } else if ( hist->getOperation() == "k+p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY]->changeMoved( !hist->isFirstMove() );
        } else if ( hist->getOperation() == "e" ) {
            if ( board[endX][endY]->getSide() == 1 ) 
                board[endX][endY - 1] = deadPool.back();
            else
                board[endX][endY + 1] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
        }
    }
}

// This function calculates the weight of board in the perspective of given side
// By default, evaluate at White
int Board::evaluateBoard(int id) {
    unsigned long long retVal = 0;
    for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++) if(board[i][j]) {
        Piece* aPiece = board[i][j];
        // get the weight of piece itself
        int pieceWeight = PIECEWEIGHT.find(aPiece->getType())->second;  
        std::map<char, vector<vector<int>>>::const_iterator it = POSWEIGHT.find(aPiece->getType());
        
        int posWeight;  // reverse the positionWeight chart if its in black perspective
        if(aPiece->getSide() == 2)  posWeight = (it->second)[7 - i][7 - j];
        else posWeight = (it->second)[i][j];
        retVal += (pieceWeight + posWeight) * ( (id == aPiece->getSide()) ? 1 : -1);
    }
    return retVal;
}   // end evaluateBoard


// this function returns the effect of a given move
int Board::evaluateMove(Move& _move) {
    Posn* init = _move.getOriginal();
    Posn* dest = _move.getEnd();
    Piece* initPiece = board[init->getX()][init->getY()];
    Piece* destPiece = board[dest->getX()][dest->getY()];
    int initPosWeight = 0, destPosWeight = 0, retVal = 0;
    if(initPiece == nullptr) {
        // std::cerr << "Init pos does not have piece at " << __LINE__ << __FILE__<<std::endl;
        return 0;
    }

    if(_move.getSide() == 1) {  // get the weight from white perspective
        initPosWeight = (POSWEIGHT.find(initPiece->getType())->second)[init->getX()][init->getY()];
        destPosWeight = (POSWEIGHT.find(initPiece->getType())->second)[dest->getX()][dest->getY()];
    } else {
        initPosWeight = (POSWEIGHT.find(initPiece->getType())->second)[7 - init->getX()][7 - init->getY()];
        destPosWeight = (POSWEIGHT.find(initPiece->getType())->second)[7 - dest->getX()][7 - dest->getY()];
    }

    if(_move.getOperation() == "c") {
        int diff = dest->getX() - init->getX();
        if(diff == 2 && initPiece->getSide() == 1 )   // white king e1->g1
            retVal += 6 + 1;    // 6 from movin King, 1 from moving rook
        else if(diff == -2 && initPiece->getSide() == 1)    // white King e1->c1
            retVal += 2 + 1;   //king moving left, 2 from moving King, 1 from moving rook
        else if(diff == 2 && initPiece->getSide() == 2) // black King e8->g8
            retVal += 6 + 1;
        else retVal += 2 + 1; // black King e8->c8
    } else if (_move.getOperation() == "p+k") {     // promotion and kill
        // queen weight - pawn weight;
        retVal += PIECEWEIGHT.find('q')->second - PIECEWEIGHT.find('p')->second;
        destPosWeight = (POSWEIGHT.find('q')->second)[dest->getX()][dest->getY()];  // q's posWeight
        retVal = retVal + destPosWeight - PIECEWEIGHT.find('p')->second;
    } else if (_move.getOperation() == "p") {   // promotion
        retVal += PIECEWEIGHT.find('q')->second - PIECEWEIGHT.find('p')->second;
        retVal = retVal + destPosWeight - initPosWeight;
    } else if (_move.getOperation() == "k") {       // capture
        if(destPiece == nullptr){
            // std::cerr << "Wrong kill generated at " << __LINE__ <<__FILE__<<std::endl;
        }
        int destPieceWeight = PIECEWEIGHT.find(destPiece->getType())->second;
        auto it = POSWEIGHT.find(destPiece->getType());
        if(destPiece->getSide() == 2)   // reverse the positionWeight if in black perspective
            destPieceWeight += (it->second)[7 - dest->getX()][7 - dest->getY()];
        else destPieceWeight += (it->second)[dest->getX()][dest->getY()];

        // kill a piece will add its self and pos weight toward the total effect
        retVal = destPosWeight - initPosWeight + destPieceWeight;   
    } else {        // just move
        retVal = destPosWeight - initPosWeight;
    }
    // std::cerr<<"Effect of the Move from " << *init << " to " << *dest << " is " << retVal << std::endl;
    return retVal;
}   // end calcEffect


// calculate the change in effect when a move from init to dest from the perspective of side
int Board::evaluateMove(Posn* init, Posn* dest, int side) {
    Piece* initPiece = board[init->getX()][init->getY()];
    if(initPiece == nullptr) {
        // std::cerr << "Init pos does not have piece at " << __LINE__ << __FILE__<<std::endl;
        return 0;
    }
    std::unique_ptr<Move> aMove = std::make_unique<Move>(*this, *init, *dest);
    return evaluateMove(*(aMove.get()));
}   // end evaluateMove

int Board::evaluateMove(const int sx, const int sy, const int ex, const int ey, const int side) {
    std::unique_ptr<Posn> st = std::make_unique<Posn>(sx, sy);
    std::unique_ptr<Posn> ed = std::make_unique<Posn>(ex, ey);
    return evaluateMove(st.get(), ed.get(), side);
}   // end evaluateMove

std::vector<std::vector<Piece *>> &Board::getBoard() { return board; }

std::vector<std::vector<Piece *>> &Board::getSetUpBoard() { return setUpBoard; }

std::vector<std::unique_ptr<Piece>> &Board::getPieces() { return pieces; }

Piece* Board::at(const int x, const int y) { return board[x][y]; }   // end at
Piece* Board::at(Posn& _pos) {return board[_pos.getX()][_pos.getY()];}
Piece* Board::at(Posn* posPtr) { return board[posPtr->getX()][posPtr->getY()];}
