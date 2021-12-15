// Kunling Yang
// Last Modified At (UTC-5) 1754, 20211208

#include "levelFour.h"
#include "player.h"
#include "game.h"

std::string LevelFour::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& my_am, const int id) {
    // std::cerr << "LevelFour AI makes Move now, at" <<__LINE__ << " in" <<__FILE__ <<std::endl;
    Player* currPlayer = nullptr;
    for(auto it : game.getPlayers()){
        if( it->getId() == id)
            currPlayer = it;
    }
    // if(!currPlayer) std::cerr << "CurrentPlayerNotFoundAt" << __LINE__ << "in" << __FILE__ << std::endl;
    int depth = 2;
    int whatever = AlphaBeta(game, currPlayer, id, depth, -0xffffff, 0xfffffff);
    whatever++;
    for(auto it: game.getPlayers()) {
        // std::cerr << "Recover the am for player " << it->getId() << std::endl;
        it->notify(game.getBoard(), *(game.getMoveHistory()));
    }

    return this->cmd;
}   // end makeMove

// Minimax returns the best moving command possible using recursive search with a specified depth
int LevelFour::AlphaBeta(Game& game, Player* currPlayer, int maxmizedID, int depth, int alpha, int beta) {
    Board& board = game.getb();
    if (depth <= 0) {
        // Evaluate Board at White Perspective
        return board.evaluateBoard();
    }
    currPlayer->notify(board.getBoard(),*(game.getMoveHistory()));  // update this player's am

    std::vector<std::unique_ptr<Move>>& am = currPlayer->getAM();

    for(auto it = am.begin(); it != am.end(); ++it) {
        Move* movePtr= it->get();
        board.smart_move(*movePtr, 'q');    // assume to take this step    

        Player* next = game.nextPlayer(currPlayer->getId());
        int currMoveEffect = -AlphaBeta(game, next, maxmizedID, depth -1, -beta, -alpha);
        if(currMoveEffect >= beta){
            board.undo(movePtr);
            return beta;
        }  
        if(currMoveEffect > alpha) {   // a better movement is found
            alpha = currMoveEffect;
            if(currPlayer->getId() == maxmizedID) {
                cmd = "move ";
                cmd.push_back(movePtr->getsx() + 'a'); cmd.push_back(movePtr->getsy() + '1');
                cmd.push_back(' ');
                cmd.push_back(movePtr->getex() + 'a');cmd.push_back(movePtr->getey() + '1');

            }

        }
        board.undo(movePtr);
    }
    return alpha;
}   // end minimax

