// Kunling Yang
// Last Modified At (UTC-5) 1754, 20211208

#include "isChecked.h"
#include "levelTwo.h"

std::string LevelTwo::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& my_am, const int side) {
    // std::cerr << __LINE__ << " " << __FILE__ << " : " << "Level 2 AI decide move" << std::endl;
    Board& board = game.getb();
    std::vector<std::unique_ptr<Move>>::iterator it;        // goes through my_available_move
    int maxCaptureWeight = -1;
    Move* select = nullptr;

    for(it = my_am.begin(); it != my_am.end(); it++) {
        Move* aMove = it->get();
        std::string op = aMove->getOperation();
        // always check move if possible
        if(IsChecked::canCheckMove(*aMove, board.getBoard())) { // if this move can check the OTHER side
            select = aMove;
            break;
        }

        if(op == "m" || op == "c")  continue;   // this move can not capture
        else if(op == "e") {                    // an en passant move
            if(PIECEWEIGHT.find('p')->second > maxCaptureWeight) {
                select = aMove;
                maxCaptureWeight = PIECEWEIGHT.find('p')->second;
            }
        } else if(op == "k") {                  // a capture exists as an available move
            char destType = tolower(board.at(aMove->getex(), aMove->getey())->getType());
            auto it2 = PIECEWEIGHT.find(destType);
            if(it2 != PIECEWEIGHT.end()) {
                if(it2 ->second > maxCaptureWeight) { // can caputure a more valuable piece
                    maxCaptureWeight = it2->second;
                    select = aMove;
                }   // end if
            } else {
                // std::cerr << __LINE__ << " " << __FILE__ << " : " << "Unkown chess type:" << destType << std::endl;
                throw "Unknown Piece type detected in levelTwo";
            }   // end if
        }   else if (op == "k+p" || op == "p+k") { // a capture + kill move
            char destType = tolower(board.at(aMove->getex(),aMove->getey())->getType());
            auto it2 = PIECEWEIGHT.find(destType);
            if(it2 != PIECEWEIGHT.end()) {
                if(it2 ->second + PIECEWEIGHT.find('q')->second > maxCaptureWeight) { 
                    maxCaptureWeight = it2->second;
                    select = aMove;
                }   // end if
            } else {
                // std::cerr << __LINE__ << " " << __FILE__ << " : " << "Unkown chess type:" << destType << std::endl;
                throw "Unknown Piece type detected in levelTwo";
            }   // end if
        }
    }   // end for loop going through am

    if(select == nullptr) { // no capture/checkable move available
        return LevelOne::makeMove(game, my_am, side);   // use LevelOne makeMove to randomly select one
    }   // end if

    std::string retStr = "move ";
    retStr.push_back(select->getsx() + 'a'); retStr.push_back(select->getsy() + '1');
    retStr.push_back( ' ');
    retStr.push_back(select->getex() + 'a'); retStr.push_back(select->getey() + '1');
    return retStr; 
}   // end makeMove
