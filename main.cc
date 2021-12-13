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
#include "bot.h"

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
        //system( "clear" );
        std::cout << "Welcome to the game of chess!" << std::endl;
        std::cout << "Select command from below:" << std::endl << std::endl;
        std::cout << "game white-player black-player allowUndo" << std::endl;
        std::cout << "setup" << std::endl << std::endl;
        std::cout << "(player can be either human or bot[1-4])" << std::endl;
        std::cout << "If do not allow undo then put in 0." << std::endl;
        std::cout << "Else put in the number of undos allowed." << std::endl;
        std::cout << "Negative for unlimited undo" << std::endl;
        std::cout << std::endl;

        std::cout << "Please enter command here: ";
        std::getline( std::cin, input );
        
        std::stringstream in{ input };
        if ( in >> cmd ) {
            std::vector<std::unique_ptr<Player>> temp;
            if ( cmd == "game" ) {          // 2 player games
                if ( in >> player ) {       // input first player
                    float score = players.size() ? players[0]->getScore() : 0;
                    if ( player == "human" ) {
                        temp.emplace_back( std::make_unique<Human>( 1, score ) );
                    } else if ( player.substr(0,3) == "bot" ) {            
                        int level = 1;
                        try{ level = std::stoi(player.substr(3)); } 
                        catch(const std::invalid_argument& ia) {  // not valid ai level
                            continue;
                        }
                        std::cerr << __LINE__ << std::endl;
                        temp.emplace_back(std::make_unique<Bot>(1, level, score));
                        std::cerr << __LINE__ << std::endl;
                    } else continue;    // unrecognized player input
                } else continue;        //no first player detected
                if ( in >> player ) {    // input second player
                    float score = players.size() ? players[0]->getScore() : 0;
                    if ( player == "human" ) {
                        temp.emplace_back( std::make_unique<Human>( 2, score ) );
                    } else if ( player.substr(0,3) == "bot" ) {
                        int level = 1;
                        try{ level = std::stoi(player.substr(3)); } 
                        catch(const std::invalid_argument& ia) {  // not valid ai level
                            continue;
                        }
                        std::cerr << "Add a bot player at level " << level << std::endl;    
                        temp.emplace_back(std::make_unique<Bot>(2, level, score));
                    } else continue;    // unrecognized player input
                } else continue;        // no second player
                if ( !(in >> numUndo) ) {
                    continue;
                } else {
                    temp[0]->changeUndo( numUndo );
                    temp[1]->changeUndo( numUndo );
                }

                std::swap( players, temp );
                g->clearPlayer();
                for ( int i = 0; i < (int)players.size(); ++i ) {
                    g->addPlayer( players[i].get() );
                }
                g->start();
            } else if ( cmd == "setup" ) {      // setup mode
                g->setup();
            }
        }
    }

    system( "clear" );

    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << g->getScore( 0 ) << std::endl;
    std::cout << "Black: " << g->getScore( 1 ) << std::endl;
}