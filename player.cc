// Zichu
// Last Modified At

#include "player.h"

const int SIZE = 8;
Player::Player( const int &id, std::vector<std::vector<Piece *>>& _board ) : 
    score{ 0 }, id{ id }, board{_board} { } // end constructor

// This function adds a Piece's every avaiable move into the avaiableMove vector
void Player::emplacePieceMove(const int x, const int y) {
    std::cerr << "Start add all avaialble move @ (" << x << y << ")" << std::endl;
    Piece* target = board[x][y];
    if(!target || target->getSide() != id)  return;
    for(int i = 0; i < SIZE; i++) {         // row
        for(int j = 0; j < SIZE; j++) {     // col
            Posn init{x,y};
            Posn dest{i,j};
            if(target->isValidMove(&init, &dest, board)) {
                char op;
                // get movement type
                if(toupper(target->getType()) == 'P' && (i == 0 || i == 7))
                    op = 'p';
                else if (toupper(target->getType()) == 'K' && abs(j - y) == 2)  // move king two steps
                    op = 'c';
                else if (board[i][j] && board[i][j]->getSide() != id)    // piece of different side
                    op = 'k';
                availableMove.emplace_back(init, dest, id, op);
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end emplace PieceMove

// This function recieves notify from the board and thus update all available movements for this player.
void Player::notify() {
    availableMove.clear();  // empty the vector
    for (int i = 0; i < 8; i++) { // search for all pieces owned by current player
        for (int j = 0; j < 8; j++) {
            if(board[i][j] && board[i][j]->getSide() == id) {
                emplacePieceMove(i, j);
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end notify

int Player::getScore() { return score; }

int Player::getId() { return id; }

Player::~Player() { }