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
    std::vector<Piece *> deadPool;
    std::vector<std::vector<Piece *>> setUpBoard;
    public:
    Board();
    void boardInit( const bool isSetup );
    void smart_move(Move&, const char promptTo);
    void undo( std::vector<Move *> &undoHist );
    void undo(Move*);
    
    // This function calculates the weight of board in the perspective of given side
    int evaluateBoard(int id = 1);
    int evaluateMove(Posn*,Posn*,int id = 1);
    int evaluateMove(const int sx, const int sy, 
        const int ex, const int ey, const int side = 1); //start & end Posn not construced
    int evaluateMove(Move&);
    Piece* at(const int, const int);
    Piece* at(Posn&);
    Piece* at(Posn*);
    std::vector<std::vector<Piece *>> &getBoard();
    std::vector<std::vector<Piece *>> &getSetUpBoard();
    std::vector<std::unique_ptr<Piece>> &getPieces();
};

#endif
