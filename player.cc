// Zichu
// Last Modified At

#include "player.h"
#include "game.h"

const int SIZE = 8;
Player::Player( const int &id, const int numUndo ) : 
    score{ 0 }, id{ id }, numUndo{ numUndo } { } // end constructor

// This function adds a Piece's every avaiable move into the avaiableMove vector
void Player::emplacePieceMove(const int x, const int y, Game &game) {
    std::cerr << "Start add all avaialble move @ (" << x << y << ")" << std::endl;
    std::vector<std::vector<Piece *>> board = game.getBoard();
    Piece* target = board[x][y];
    if(!target || target->getSide() != id)  return;
    for(int j = 0; j < SIZE; j++) {         // row
        for(int i = 0; i < SIZE; i++) {     // col
            Posn init{x,y};
            Posn dest{i,j};
            if(target->isValidMove(&init, &dest, board, game.getMoveHistory())) {
                std::string op = "m";
                // get movement type
                std::cerr << __LINE__ << std::endl;
                if(toupper(target->getType()) == 'P' && (i == 0 || i == 7))
                    op = "p";
                else if (toupper(target->getType()) == 'K' && abs(j - y) == 2)  // move king two steps
                    op = "c";
                else if (board[i][j] && board[i][j]->getSide() != id)    // piece of different side
                    op = "k";
                std::cerr << __LINE__ << std::endl;
                availableMove.emplace_back(
                    std::make_unique<Move>( x, y, i, j, id, op, 
                        board[x][y]->isMoved() ) );
            }   // end if
        }   // end col for loop
    }   // end row for loop
    std::cerr << "End add all avaialble move @ (" << x << y << ")" << std::endl;
}   // end emplace PieceMove

// This function recieves notify from the board and thus update all available movements for this player.
void Player::notify( Game &game ) {
    availableMove.clear();  // empty the vector
    std::vector<std::vector<Piece *>> board = game.getBoard();
    for (int i = 0; i < (int)board.size(); i++) { // search for all pieces owned by current player
        for (int j = 0; j < (int)board[i].size(); j++) {
            if(board[i][j] && board[i][j]->getSide() == id) {
                emplacePieceMove(i, j, game);
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end notify

float &Player::getScore() { return score; }

int Player::getId() { return id; }

int Player::getNumUndo() { return numUndo; }

void Player::usedUndo() { numUndo--; }

bool Player::hasAvaliableMove() { return availableMove.size() > 0; }

Player::~Player() { }