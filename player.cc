// Zichu
// Last Modified At (UTC-5) 1942, 20211210

#include "player.h"
#include "game.h"
#include "isChecked.h"
const int SIZE = 8;

Player::Player(const int _id, const float score ) : // team specified
    score{ score }, id{_id}, numUndo{ 0 }   { }

// This function adds a Piece's (at x,y) every avaiable move into the avaiableMove vector
void Player::emplacePieceMove( const int x, const int y, 
    std::vector<std::vector<Piece *>> &board, MoveHistory &mh ) {
//std::cerr << "Start add all avaialble move at Posn" << Posn{x,y} << std::endl;
    Piece* target = board[x][y];
    Move* lastMove = mh.lastMove();
    if(!target || target->getSide() != id)  return;
    for(int j = 0; j < SIZE; j++) {         // row
        for(int i = 0; i < SIZE; i++) {     // col
            Posn init{x,y};
            Posn dest{i,j};
            if( target->isValidMove(&init, &dest, board, &mh) &&    // make sure can go there
                !IsChecked::isCheckMove(x, y, i, j, id, board)) {
                std::string op = "m";
                // generate movement type
                if(tolower(target->getType()) == 'p' && (j == 0 || j == 7)){
                    if(x != i){     // move to another column
//std::cerr << "add a p+k from" << init << " to " << dest << " at " << __LINE__ << " of " << __FILE__ <<std::endl;
                        op = "k+p";
                    } else {     // goes to a different row, means  promotion and kill
//std::cerr << "add a p from" << init << " to " << dest << " at " << __LINE__ << " of " << __FILE__ <<std::endl;
                        op = "p";  // just promotion
                    }
                }
                else if (tolower(target->getType()) == 'k' && std::abs(j - y) == 2)  // move king two steps
                    op = "c";
                else if (board[i][j] && board[i][j]->getSide() != id)    // piece of different side
                    op = "k";
                // if an enemy pawn is advancing two steps in its first move and goes to a adjacent
                // cell on the same row as a friendly pawn
                else if (lastMove != nullptr && tolower(target->getType()) == 'p' && lastMove->isFirstMove() &&
                    board[lastMove->getex()][lastMove->getey()]->getType() == 'p' &&
                    std::abs(lastMove->getey() - lastMove->getsy()) == 2 && 
                    std::abs(lastMove->getex() - x) == 1 && lastMove->getey() == y &&
                    i == lastMove->getsx()) {
                    op = "e"; 
                }   // end operation type judge

                if(!IsChecked::isCheckMove(x, y, i, j, id, board)){
                    availableMove.emplace_back(
                        std::make_unique<Move>( x, y, i, j, id, op, 
                            board[x][y]->isMoved() ) );
                }
            }   // end if
        }   // end col for loop
    }   // end row for loop
}   // end emplace PieceMove

// This function recieves notify from the board and thus update all available movements for this player.
void Player::notify( std::vector<std::vector<Piece *>> &board, MoveHistory &mh ) {
    availableMove.clear();  // empty the vector
    // std::cerr << __LINE__ << std::endl;
    for (int i = 0; i < (int)board.size(); i++) { // search for all pieces owned by current player
        for (int j = 0; j < (int)board[i].size(); j++) {
            if(board[i][j] != nullptr && board[i][j]->getSide() == id) {
                emplacePieceMove(i, j, board, mh);
            }   // end if
        }   // end col for loop
    }   // end row for loop
    // std::cerr << __LINE__ << std::endl;
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
