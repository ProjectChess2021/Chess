#include <iostream>
#include <memory>
#include "game.h"
#include "human.h"
#include "textDisplay.h"
#include <sstream>
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"

int main() {
    std::vector<std::unique_ptr<Player>> players;
    std::string input = "";
    std::string cmd = "";
    std::string player = "";
    int numUndo;
    bool end = false;
    std::unique_ptr<Game> g = std::make_unique<Game>();

    while ( !std::cin.eof() && !end ) {
        system( "clear" );
        std::cout << "Welcome to the game of chess!" << std::endl;
        std::cout << "Select command from below:" << std::endl << std::endl;
        std::cout << "game white-player black-player allowUndo" << std::endl;
        std::cout << "setup" << std::endl << std::endl;
        std::cout << "(player can be either human or computer[1-4])" << std::endl;
        std::cout << "If do not allow undo then put in 0, else put in the number"
            << " of undos allowed. -1 for unlimited undo" << std::endl;
        std::cout << std::endl;

        std::cout << "Please make command here: ";
        std::getline( std::cin, input );
        
        std::stringstream in{ input };
        if ( in >> cmd ) {
            if ( cmd == "game" ) {
                if ( in >> player ) {
                    if ( !in >> numUndo ) {
                        continue;
                    }
                    if ( player == "human" ) {
                        players.emplace_back( std::make_unique<Human>( 1, numUndo ) );
                    } else if ( player == "computer1" ) {
                        // emplace_back a computer1 to players
                    } else if ( player == "computer2" ) {
                        // emplace_back a computer2 to players
                    } else if ( player == "computer3" ) {
                        // emplace_back a computer3 to players
                    } else if ( player == "computer4" ) {
                        // emplace_back a computer4 to players
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
                if ( in >> player ) {
                    if ( !in >> numUndo ) {
                        continue;
                    }
                    if ( player == "human" ) {
                        players.emplace_back( std::make_unique<Human>( 2, numUndo ) );
                    } else if ( player == "computer1" ) {
                        // emplace_back a computer1 to players
                    } else if ( player == "computer2" ) {
                        // emplace_back a computer2 to players
                    } else if ( player == "computer3" ) {
                        // emplace_back a computer3 to players
                    } else if ( player == "computer4" ) {
                        // emplace_back a computer4 to players
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }

                std::unique_ptr<TextDisplay> td = std::make_unique<TextDisplay>();
                g->attach( td.get() );

                for ( int i = 0; i < 2; ++i ) {
                    g->addPlayer( players[i].get() );
                }
                while ( !std::cin.eof() ) {
                    g->start();
                }
                end = true;
            } else if ( cmd == "setup" ) {
                g->setup();
            }
        }
    }

    system( "clear" );

    std::cout << std::endl;
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << g->getScore( 0 ) << std::endl;
    std::cout << "Black: " << g->getScore( 1 ) << std::endl;
}