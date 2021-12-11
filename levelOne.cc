// Kunling Yang
// Last Modified At (UTC-5) 1708, 20211208

#include "levelOne.h"
#include <ctime>
#include <random>

// use the board and available movement vector to randomly pick a possible movement
std::string LevelOne::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& am, const int side) {
    std::cerr << "Level1 AI makesMove now @ Line10, LevleOne.cc.";
    int capacity = am.size();
    srand(time(nullptr));
    int pickedNum = rand() % capacity;     // generate a number from 0 to capacity - 1
    std::string retStr;
    Posn* init = am.at(pickedNum)->getOriginal();   // initial position ptr
    Posn* dest = am.at(pickedNum)->getEnd();        // destination position ptr
    retStr = "move " + (char) (init->getY() + 'a') + (init->getX());
    retStr += " " +  (char) (dest->getY() + 'a') + (dest->getX());
    std::cerr << "Produced str:" << retStr;
    return retStr;
}   // end makeMove