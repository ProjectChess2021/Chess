// Kunling Yang
// Last Modified At (UTC-5) 1708, 20211208

#include "levelOne.h"
#include <ctime>
#include <sstream>
#include <random>

// use the board and available movement vector to randomly pick a possible movement
std::string LevelOne::makeMove(Game& game, std::vector<std::unique_ptr<Move>>& am, const int side) {
    int capacity = am.size();
    srand(time(nullptr));
    int pickedNum = rand() % capacity;     // generate a number from 0 to capacity - 1
    std::string retStr = "move ";
    Posn* init = am.at(pickedNum)->getOriginal();   // initial position ptr
    Posn* dest = am.at(pickedNum)->getEnd();        // destination position ptr
    retStr.push_back(init->getX() + 'a');retStr.push_back(init->getY() + '1');
    retStr.push_back(' ');
    retStr.push_back(dest->getX() + 'a');retStr.push_back(dest->getY() + '1');
    return retStr;
}   // end makeMove
