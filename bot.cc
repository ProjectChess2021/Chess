// Kunling
// Last Modified At (UTC-5) 0153,20211211
#include "bot.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"

Bot::Bot(const int _id, const int level, const float score) : Player{_id, score} {
    setStrategy(level);
}   // end constructor

// This function changes the strategy (the difficulty) AI adapts
void Bot::setStrategy(const int difficulty) {
    if(difficulty == 1) _strategy = std::make_unique<LevelOne>();
    else if(difficulty == 2) _strategy = std::make_unique<LevelTwo>();
    else if(difficulty == 3) _strategy = std::make_unique<LevelThree>();
    else if(difficulty == 4) _strategy = std::make_unique<LevelFour>();
}   // end setStrategy

// return the command AI put based on current Strategy
std::string Bot::cmd(Game &game) {
    std::string retStr = _strategy->makeMove(game,getAM(),getId());
    return retStr;
}   // end cmd

char Bot::promptTo() {
    return 'q';
}
