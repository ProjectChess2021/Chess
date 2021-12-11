// Kunling
// Last Modified At (UTC-5)

#include "levelThree.h"

// calculate the change in effect when a piece performs given _move
int calcEffect(Posn* init, Posn* dest, char type) {
     // the effect of this move, new Effect - old effect
    std::map<char, vector<vector<int>>>::const_iterator it = POSWEIGHT.find(type);
    return (it->second)[dest->getX()][dest->getY()] -(it->second)[init->getX()][init->getY()];
}   // end calculateEffect

// Level Three AI tries not to get the pieces captured, if no pieces are possible to be captured
// it will try to make a capture move (Level Two)
// if no capture is possible, a random move is selected
std::string LevelThree::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& my_am, const int side) {
    std::cerr << "LevelThree AI makes Move now, at" <<__LINE__ << " in" <<__FILE__ <<std::endl;
    int maxCaptureWeight = -1;  // the most valuable pieces can be captured this turn
    int minEffect = 0xffffffff;  
    Posn* maxPosn = nullptr;
    Piece* maxPiece = nullptr;

    std::vector<std::vector<Piece *>> &board = game.getBoard();
    std::vector<Player*>& playerLst = game.getPlayers();
    std::vector<std::vector<int>> controlArea;
    controlArea.resize(8, std::vector<int>(8, -100));

    Player* opponentPtr = nullptr;

    for(long unsigned int i = 0; i < playerLst.size(); i++)
        if(playerLst[i]->getId() != side) opponentPtr = playerLst[i];
    
    std::vector<std::unique_ptr<Move>>& opponentAM = opponentPtr->getAM();
    std::vector<std::unique_ptr<Move>>::iterator it;

    for(it = opponentAM.begin(); it != opponentAM.end(); it++) {    // looking for enemy capture
        Move* aMove = it->get();
        Posn* dest = aMove->getEnd();
        Posn* init = aMove->getOriginal();
        char initType = tolower(board[init->getX()][init->getY()]->getType());
        char destType = tolower(board[dest->getX()][dest->getY()]->getType());
        controlArea[dest->getX()][dest->getY()] = std::max(calcEffect(init,dest,initType),
                                                      controlArea[dest->getX()][dest->getY()]);
        if(aMove->getOperation() == "k") {    // a capture exists as an available move
            auto it2 = PIECEWEIGHT.find(destType);
            if(it2 != PIECEWEIGHT.end()) {
                if(it2 ->second > maxCaptureWeight) { // can caputure a more valuable piece
                    maxCaptureWeight = it2->second;
                    maxPosn = aMove->getEnd();
                    maxPiece = board[dest->getX()][dest->getY()];
                }   // end if
            }   // end if
        }   // end if
    }   // end for loop going through am

    if(maxCaptureWeight == -1)  // enemy is impossible to caputure a piece
        return LevelTwo::makeMove(game, my_am, side);
    int destX = -1, destY = -1;
    for(std::vector<std::unique_ptr<Move>>::iterator it = my_am.begin(); it != my_am.end(); ++it) {
        Move* aMove = it->get();
        if(aMove->getOriginal() == maxPosn){
            int currEffect = calcEffect(maxPosn,aMove->getEnd(),maxPiece->getType());
            if(currEffect < minEffect){     // found a better move
                destX = aMove->getEnd()->getX();
                destY = aMove->getEnd()->getY();
                minEffect = currEffect;
            }
        }
    }   // end for
    std::string retStr = "move " + (char) (maxPosn->getX() + 'a') + (maxPosn->getY());
    retStr += " " +  std::to_string(destX + 'a') + std::to_string(destY);
    std::cerr << "Capture move found @ Line 38, LevelTwo.cc. Produced str:" << retStr;
    return retStr; 
}   // end makeMove
