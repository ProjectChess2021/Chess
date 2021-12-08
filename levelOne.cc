// Kunling Yang
// Last Modified At (UTC-5) 1708, 20211208

#include "levelOne.h"
#include <ctime>
#include <random>

// use the board and available movement vector to randomly pick a possible movement
std::string LevelOne::makeMove(std::vector<std::vector<Piece *>>& board, std::vector<Move>& am) {
    std::cerr << "Level1 AI makesMove now @ Line10, LevleOne.cc.";
    int capacity = am.size();
    srand(time(nullptr));
    int pickedNum = rand() % capacity;     // generate a number from 0 to capacity - 1
    std::string retStr;
    Posn* init = am[pickedNum].getOriginal();   // initial position ptr
    Posn* dest = am[pickedNum].getEnd();        // destination position ptr
    retStr = "move " + (char) (init->getY() + 'a') + (init->getX());
    retStr += " " +  (char) (dest->getY() + 'a') + (dest->getX());
    std::cerr << "Produced str:" << retStr;
    return retStr;
}   // end makeMove