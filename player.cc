// Zichu
// Last Modified At

#include "player.h"
#include "game.h"

const int SIZE = 8;
Player::Player( const int &id ) : 
    score{ 0 }, id{ id } { } // end constructor

// This function adds a Piece's every avaiable move into the avaiableMove vector
void Player::emplacePieceMove(const int x, const int y, Game &game) {
    std::cerr << "Start add all avaialble move @ (" << x << y << ")" << std::endl;
    std::vector<std::vector<Piece *>> board = game.getBoard();
    Piece* target = board[x][y];
    if(!target || target->getSide() != id)  return;
    for(int i = 0; i < SIZE; i++) {         // row
        for(int j = 0; j < SIZE; j++) {     // col
            Posn init{x,y};
            Posn dest{i,j};
            if(target->isValidMove(&init, &dest, board, game.getMoveHistory())) {
                std::string op;
                // get movement type
                if(toupper(target->getType()) == 'P' && (i == 0 || i == 7))
                    op = "p";
                else if (toupper(target->getType()) == 'K' && abs(j - y) == 2)  // move king two steps
                    op = "c";
                else if (board[i][j] && board[i][j]->getSide() != id)    // piece of different side
                    op = "k";
                availableMove.emplace_back(init, dest, id, op, (1 && board[i][j]->isMoved()));
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end emplace PieceMove

// This function recieves notify from the board and thus update all available movements for this player.
void Player::notify( Game &game ) {
    availableMove.clear();  // empty the vector
    std::vector<std::vector<Piece *>> board = game.getBoard();
    for (int i = 0; i < 8; i++) { // search for all pieces owned by current player
        for (int j = 0; j < 8; j++) {
            if(board[i][j] && board[i][j]->getSide() == id) {
                emplacePieceMove(i, j, game);
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end notify

float &Player::getScore() { return score; }

int Player::getId() { return id; }

bool Player::hasAvaliableMove() { return availableMove.size() > 0; }

Player::~Player() { }