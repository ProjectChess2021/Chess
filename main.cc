#include <iostream>
#include <memory>
#include "game.h"
#include "human.h"

int main() {
    std::vector<std::unique_ptr<Player>> players;
    players.emplace_back( std::make_unique<Human>( 1 ) );
    players.emplace_back( std::make_unique<Human>( 2 ) );
    std::vector<Player *> playerOfTheGame;
    playerOfTheGame.emplace_back( players[0].get() );
    playerOfTheGame.emplace_back( players[1].get() );
    std::unique_ptr<Game> g = std::make_unique<Game>( playerOfTheGame );
}