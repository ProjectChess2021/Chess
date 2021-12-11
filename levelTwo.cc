// Kunling Yang
// Last Modified At (UTC-5) 1754, 20211208

#include "levelTwo.h"

std::string LevelTwo::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& am, const int side) {
    std::cerr << "Level2 AI makesMove now @ Line7, LevelTwo.cc.";
    std::vector<std::vector<Piece *>> &board = game.getBoard();
    std::vector<std::unique_ptr<Move>>::iterator it;
    int maxCaptureWeight = -1;
    Posn* maxCaptureInit = nullptr;
    Posn* maxCaptureDest = nullptr;

    for(it = am.begin(); it != am.end(); it++) {
        Move* aMove = it->get();
        if(aMove->getOperation() == "k") {    // a capture exists as an available move
            int destX = aMove->getEnd()->getX();
            int destY = aMove->getEnd()->getY();
            char destType = tolower(board[destX][destY]->getType());
            
            auto it2 = PIECEWEIGHT.find(destType);
            if(it2 != PIECEWEIGHT.end()) {
                if(it2 ->second > maxCaptureWeight) { // can caputure a more valuable piece
                    maxCaptureWeight = it2->second;
                    maxCaptureInit = aMove->getOriginal();
                    maxCaptureDest = aMove->getEnd();
                }   // end if
            }   // end if
        }   // end if
    }   // end for loop going through am

    if(maxCaptureWeight == -1) { // no capture move available
        std::cerr << "No capture move available @ Line31, LevelTwo.cc";
        return LevelOne::makeMove(game, am, side);   // use LevelOne makeMove to randomly select one
    }   // end if
    
    std::string retStr;
    retStr = "move " + (char) (maxCaptureInit->getY() + 'a') + (maxCaptureInit->getX());
    retStr += " " +  (char) (maxCaptureDest->getY() + 'a') + (maxCaptureDest->getX());

    std::cerr << "Capture move found @ Line 38, LevelTwo.cc. Produced str:" << retStr;
    return retStr; 
}   // end makeMove
