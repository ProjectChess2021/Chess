// Kunling Yang
// Last Modified At (UTC-5) 1754, 20211208

#include "levelFour.h"
#include "player.h"
#include "game.h"

const int DEPTH = 2;

std::string LevelFour::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& my_am, const int id) {
    std::cerr << "LevelFour AI makes Move now, at" <<__LINE__ << " in" <<__FILE__ <<std::endl;
    Player* currPlayer = nullptr;
    for(auto it : game.getPlayers()){
        if( it->getId() == id)
            currPlayer = it;
    }
    if(!currPlayer) std::cerr << "CurrentPlayerNotFoundAt" << __LINE__ << "in" << __FILE__ << std::endl;
    int bestMove = minimax(4, game, currPlayer, id);
    std::cerr << "BestMoveValueIs" << bestMove << ". TheReturnStringIs:"<<this->cmd<<std::endl;
    return this->cmd;
}   // end makeMove

// Minimax returns the best moving command possible using recursive search with a specified depth
int LevelFour::minimax(int depth, Game& game, Player* currPlayer, int maximizedId) {
    std::string retStr = "";
    Board& board = game.getb();
    if (depth <= 0) {
        // NOTE: check for four players, cause the id might not be 1 or 2
        return board.evaluateBoard(maximizedId);
    }
    int bestBoard = -9999;
    currPlayer->notify(board.getBoard(),*(game.getMoveHistory()));   // update this player's availableMoveList
    std::vector<std::unique_ptr<Move>>& am = currPlayer->getAM();
    for(auto it = am.begin(); it != am.end(); ++it) {
        Move* movePtr= it->get();
        board.smart_move(*movePtr, 'q');
        Player* next = game.nextPlayer(currPlayer->getId());

        int currBoard = minimax(depth - 1, game, next, maximizedId);
        if(currBoard > bestBoard) {   // a better movement is found
            this->cmd = "move " + (char)(movePtr->getsx() + 'a') + (char)(movePtr->getsy());
            this->cmd += " " + (char)(movePtr->getex() + 'a' ) + (char)(movePtr->getey());
            bestBoard = currBoard;
        }
        board.undo(movePtr);
    }
    return bestBoard;
}   // end minimax
