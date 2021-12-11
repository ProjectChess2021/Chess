#include <iostream>
#include <memory>
#include "game.h"
#include "human.h"
#include "textDisplay.h"
#include <sstream>
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "graphicDisplay.h"

int main() {
    std::vector<std::unique_ptr<Player>> players;
    std::string input = "";
    std::string cmd = "";
    std::string player = "";
    int numUndo;
    bool end = false;
    std::unique_ptr<Game> g = std::make_unique<Game>();
    std::unique_ptr<TextDisplay> td = std::make_unique<TextDisplay>();
    // std::unique_ptr<GraphicDisplay> gd = std::make_unique<GraphicDisplay>( 8, 8 );
    g->attach( td.get() );
    // g->attach( gd.get() );

    while ( !std::cin.eof() && !end ) {
        system( "clear" );
        std::cout << "Welcome to the game of chess!" << std::endl;
        std::cout << "Select command from below:" << std::endl << std::endl;
        std::cout << "game white-player black-player allowUndo" << std::endl;
        std::cout << "setup" << std::endl << std::endl;
        std::cout << "(player can be either human or computer[1-4])" << std::endl;
        std::cout << "If do not allow undo then put in 0." << std::endl;
        std::cout << "Else put in the number of undos allowed." << std::endl;
        std::cout << "Negative for unlimited undo" << std::endl;
        std::cout << std::endl;

        std::cout << "Please enter command here: ";
        std::getline( std::cin, input );
        
        std::stringstream in{ input };
        if ( in >> cmd ) {
            std::vector<std::unique_ptr<Player>> temp;
            if ( cmd == "game" ) {
                if ( in >> player ) {
                    if ( player == "human" ) {
                        if ( players.size() == 2 ) {
                            int score = players[0]->getScore();
                            temp.emplace_back( 
                                std::make_unique<Human>( 1, score ) );
                        } else if ( players.size() == 4) {
                            int score = players[0]->getScore();
                            temp.emplace_back( 
                                std::make_unique<Human>( 1, score ) );
                        } else {
                            temp.emplace_back( 
                                std::make_unique<Human>( 1 ) );
                        }
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
                    if ( player == "human" ) {
                        if ( players.size() == 2 ) {
                            float score = players[1]->getScore();
                            temp.emplace_back( 
                                std::make_unique<Human>( 2, score ) );
                        } else if ( players.size() == 4) {
                            float score = players[2]->getScore();
                            temp.emplace_back( 
                                std::make_unique<Human>( 2, score ) );
                        } else {
                            temp.emplace_back( 
                                std::make_unique<Human>( 2 ) );
                        }
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

                if ( !(in >> numUndo) ) {
                    continue;
                } else {
                    temp[0]->changeUndo( numUndo );
                    temp[1]->changeUndo( numUndo );
                }

                std::cerr << __LINE__ << std::endl;

                std::swap( players, temp );

                std::cerr << __LINE__ << std::endl;

                g->clearPlayer();

                std::cerr << __LINE__ << std::endl;

                for ( int i = 0; i < (int)players.size(); ++i ) {
                    g->addPlayer( players[i].get() );
                }

                std::cerr << __LINE__ << std::endl;
                g->start();
            } else if ( cmd == "setup" ) {
                g->setup();
            }
        }
    }

    system( "clear" );

    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << g->getScore( 0 ) << std::endl;
    std::cout << "Black: " << g->getScore( 1 ) << std::endl;
}