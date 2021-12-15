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
using std::cout;
using std::endl;

// // This function prints a lot of newline character as if SYS("clear")
// void screenClear() {
//     for(int i = 0; i < 20; i ++)    cout << endl;
// }   // end screenClear()


int main() {
    std::vector<std::unique_ptr<Player>> players;
    std::string input = "";
    std::string cmd = "";
    std::string player = "";
    int numUndo, a;
    std::unique_ptr<Game> g = std::make_unique<Game>();
    std::unique_ptr<TextDisplay> td = std::make_unique<TextDisplay>();
    std::unique_ptr<GraphicDisplay> gd = std::make_unique<GraphicDisplay>( 8, 8 );
    g->attach( td.get() );
    g->attach( gd.get() );

    try{ while ( !std::cin.eof() ) {
        // a = system( "clear" );
        for(int i = 0; i < 20; i ++)    cout << endl;
        cout << "               Welcome to the game of chess created together by Zichu Wu, Kunling Yang, Min!           " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Available commands are all listed below:"<< endl;
        cout << "  -  game white-player black-player allowUndo" << endl;
        cout << "         (player can be either \"human\" or \"computer[1-4])\". If you wish to prohibit undo, type in 0 for " << endl;
        cout << "          allowUndo; if unlimited undo is desired, type in any negative integer; otherwise, type in the number of" << endl;
        cout << "          undos allowed for each player." <<endl;
        cout << "          e.g. \"game human bot4 0\" will start a game with Level4 AI that does not allow undo.)"  << endl;     
        cout << endl;
        cout << "  -  setup" << endl;
        cout << "          (This command enters the setup mode and allows client to put pieces freely as long as it's valid)" << endl;
        cout << endl;

        cout << "Please enter command here: ";
        std::getline( std::cin, input );
        
        std::stringstream in{ input };
        if ( in >> cmd ) {
            std::vector<std::unique_ptr<Player>> temp;
            if ( cmd == "game" ) {          // 2 player games
                if ( in >> player ) {       // input first player
                    float score = players.size() ? players[0]->getScore() : 0;
                    if ( player == "human" ) {
                        temp.emplace_back( std::make_unique<Human>( 1, score ) );
                    } else if ( player.substr(0,8) == "computer" ) {            
                        int level = 1;
                        try{ level = std::stoi(player.substr(3)); } 
                        catch(const std::invalid_argument& ia) {  // not valid ai level
                            continue;
                        }
                        temp.emplace_back(std::make_unique<Bot>(1, level, score));
                    } else continue;    // unrecognized player input
                } else continue;        //no first player detected
                if ( in >> player ) {    // input second player
                    float score = players.size() ? players[1]->getScore() : 0;
                    if ( player == "human" ) {
                        temp.emplace_back( std::make_unique<Human>( 2, score ) );
                    } else if ( player.substr(0,8) == "computer" ) {
                        int level = 1;
                        try{ level = std::stoi(player.substr(3)); } 
                        catch(const std::invalid_argument& ia) {  // not valid ai level
                            continue;
                        }  
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
                cout << "Entering the setup mode" << endl;
                g->setup();
            }
        }
    }

    // a = system( "clear" );
    a++;
    cout << "Final Score:" << endl;
    cout << "White: " << g->getScore( 0 ) << endl;
    cout << "Black: " << g->getScore( 1 ) << endl;
    } catch (...) { cout << "Unexpected Behaviour meeted Program will be terminated."  << endl;}
}
