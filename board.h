#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <memory>
#include "subject.h"
#include "piece.h"
#include "rook.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "piece.h"
#include "move.h"

class Board {
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<std::vector<Piece *>> board;
    std::vector<std::vector<Piece *>> setUpBoard;
    std::vector<Piece *> deadPool;

    public:
    Board();
    void boardInit( const bool isSetup );

    void move( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY );
    void kill( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY );
    void castle( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY );
    void promotion( const int &originalX, const int &originalY,
        const int &finalX, const int &finalY, const char promptTo );
    void killNProm( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY, const char promptTo );
    void CEP( const int &originalX, const int &originalY, 
      const int &finalX, const int &finalY );
    void smart_move(Move&);
    void undo( std::vector<Move *> &undoHist );
    
    // This function calculates the weight of board in the perspective of given side
    int evaluateBoard(int);
    int evaluateMove(Posn*,Posn*,int);
    int evaluateMove(const int sx, const int sy, 
        const int ex, const int ey, const int side); //start & end Posn not construced
    int evaluateMove(Move&);
    Piece* at(const int, const int);
    Piece* at(Posn&);
    Piece* at(Posn*);
    std::vector<std::vector<Piece *>> &getBoard();
    std::vector<std::vector<Piece *>> &getSetUpBoard();
    std::vector<std::unique_ptr<Piece>> &getPieces();
};

#endif