// Zichu
// Last Modified At (UTC-5) 1942, 20211210

#include "player.h"
#include "game.h"
#include "isChecked.h"
const int SIZE = 8;

Player::Player(const int _id, const float score ) : // team specified
    score{ score }, id{_id}, numUndo{ 0 }   { }

// This function adds a Piece's every avaiable move into the avaiableMove vector
void Player::emplacePieceMove( const int x, const int y, 
    std::vector<std::vector<Piece *>> &board, MoveHistory &mh ) {
//std::cerr << "Start add all avaialble move at Posn" << Posn{x,y} << std::endl;
    Piece* target = board[x][y];
    if(!target || target->getSide() != id)  return;
    for(int j = 0; j < SIZE; j++) {         // row
        for(int i = 0; i < SIZE; i++) {     // col
            Posn init{x,y};
            Posn dest{i,j};
            if( target->isValidMove(&init, &dest, board, &mh) && 
                !IsChecked::isCheckMove(x,y,i,j,target->getSide(),board)) {
                std::string op = "m";
                // get movement type
                if(toupper(target->getType()) == 'P' && (j == 0 || j == 7)){
                    if(x != i){
std::cerr << "add a p+k from" << init << " to " << dest << " at " << __LINE__ << " of " << __FILE__ <<std::endl;
                        op = "k+p";
                    } else {     // goes to a different row, means  promotion and kill
std::cerr << "add a p from" << init << " to " << dest << " at " << __LINE__ << " of " << __FILE__ <<std::endl;
                        op = "p";  // just promotion
                    }
                }  else if (toupper(target->getType()) == 'K' && abs(j - y) == 2)  // move king two steps
                    op = "c";
                else if (board[i][j] && board[i][j]->getSide() != id)    // piece of different side
                    op = "k";

                if(!IsChecked::isCheckMove(x, y, i, j, id, board)){
                    std::cerr << "Moving from " << x << y << " to " << i << j << std::endl;
                    availableMove.emplace_back(
                        std::make_unique<Move>( x, y, i, j, id, op, 
                            board[x][y]->isMoved() ) );
                }
            }   // end if
        }   // end col for loop
    }   // end row for loop
// std::cerr << "End add all avaialble move @ " << Posn{x,y} << std::endl;
}   // end emplace PieceMove

// This function recieves notify from the board and thus update all available movements for this player.
void Player::notify( std::vector<std::vector<Piece *>> &board, MoveHistory &mh ) {
    availableMove.clear();  // empty the vector
    for (int i = 0; i < (int)board.size(); i++) { // search for all pieces owned by current player
        for (int j = 0; j < (int)board[i].size(); j++) {
            if(board[i][j] && board[i][j]->getSide() == id) {
                emplacePieceMove(i, j, board, mh);
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end notify

float &Player::getScore() { return score; }

int Player::getId() { return id; }

int Player::getNumUndo() { return numUndo; }

void Player::usedUndo() { numUndo--; }

bool Player::hasAvaliableMove() { return availableMove.size() > 0; }

std::vector<std::unique_ptr<Move>>& Player::getAM() {
    return availableMove;
}   // end getAM

void Player::changeUndo( const int num ) { numUndo = num; }

Player::~Player() { }