// Kunling
// Last Modified At (UTC-5)

#include "levelThree.h"
#include "board.h"
using std::max;

LevelThree::LevelThree() : showControl{false}{} // end constructor

void LevelThree::setControlRender(bool _var) {showControl = _var;}

// Level Three AI tries not to get the pieces captured, if no pieces are possible to be captured
// it will try to make a capture move (Level Two)
// if no capture is possible, a random move is selected
std::string LevelThree::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& my_am, const int side) {
    // std::cerr << "LevelThree AI makes Move now, at" <<__LINE__ << " in" <<__FILE__ <<std::endl;
    Board& board = game.getb();
    std::vector<std::vector<int>> controlArea; 
    // 2 if strongly controled, any Piece will be captured if move there
    // 1 if that position can only be captured by En Passant
    // 0 if not controled at all
    controlArea.resize(8, std::vector<int>(8, 0));
    Player* opponentPtr = game.nextPlayer(side);
    
    std::vector<std::unique_ptr<Move>>& opponentAM = opponentPtr->getAM();
    std::vector<std::unique_ptr<Move>>::iterator it;
    for(it = opponentAM.begin(); it != opponentAM.end(); it++) {    // looking for enemy capture
        Move* aMove = it->get();
        std::string op = aMove->getOperation(); // do not check for pawn
        if(board.at(aMove->getOriginal())->getType() == 'p')    continue;   
        // mark the destination as controled area
        controlArea[aMove->getex()][aMove->getey()] = 2;
    }   // end for loop going through am
    // mannual check for pawn
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j++) {
            if( board.at(i,j) && board.at(i,j)->getType() == 'p' && board.at(i,j)->getSide() == opponentPtr->getId() ){
                int x1 =  i - 1, x2 = i + 1, y = j;
                // DEBUG: next line unexpected behaviour when four players
                // strong control
                y = opponentPtr->getId() == 1 ?  j + 1 : j - 1;
                if(0 <= x1 && x1 < 8 && 0 <= y && y < 8)    controlArea[x1][y] = 2;
                else if(0 <= x2 && x2 < 8 && 0 <= y && y < 8)    controlArea[x2][y] = 2;
                
                // en Passant check, week control
                if((j == 3 && opponentPtr->getId() == 2) || // a black pawn EP
                (j == 4 && opponentPtr->getId() == 1)) { // white pawn EP    
                    if(0 <= x1 && x1 < 8)   
                        controlArea[x1][j] = max(controlArea[x1][j],1);
                    else if(0 <= x2 && x2 < 8) 
                        controlArea[x2][j] = max(controlArea[x2][j],1);

                }  
            }
        }
    }
                
    if(showControl){
        for(int i = 7; i >=0; i--){
            std::cout<< i + 1 << " ";
            for(int j = 0; j < 8;j++)   
                std::cout<<controlArea[j][i];
            std::cout<<std::endl;}
        std::cout << "  ";
        for(int i =0; i < 8; i ++)  std::cout << (char) (i + 'a');
        std::cout<<std::endl;
    }
    
    Move* select = nullptr;
    int maxEffect = -0xfffff; 
    for(auto it = my_am.begin(); it != my_am.end(); ++it) {
        Move* aMove = it->get();
        char type = board.at(aMove->getOriginal())->getType();
        int level = (type == 'p' && board.at(aMove->getOriginal())->isMoved()) ? 0 : 1;
        if(controlArea[aMove->getex()][aMove->getey()] > level)     // dangerous destination
            continue;
        // guarantee the destination is safe
        int currEffect = board.evaluateMove(*aMove);    // effect of this move
        if( controlArea[aMove->getsx()][aMove->getsy()] > level) {  // start point is controlled
            // make this move saves this piece from being captured
            currEffect += PIECEWEIGHT.find(type)->second;   
        }

        if(currEffect > maxEffect){     // found a better move
                select = aMove;
                maxEffect = currEffect;
        }   // end update current best and selectio
    }   // end for

    if(!select)  {  // impossible to escape or have a safe move (a move cannot be captured)
        // std::cerr << __LINE__ << " " << __FILE__ <<" : Impossible to escape\n" << std::endl;
        return LevelTwo::makeMove(game, my_am, side);  
    }
    std::string retStr = "move ";
    retStr.push_back(select->getsx() + 'a'); retStr.push_back(select->getsy() + '1');
    retStr.push_back(' ');
    retStr.push_back(select->getex() + 'a');retStr.push_back(select->getey() + '1');
    // std::cerr << __LINE__ << " " << __FILE__ <<" : Level Three decision: " << retStr << std::endl;
    return retStr; 
}   // end makeMove
