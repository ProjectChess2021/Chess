// Kunling Yang
// Last Modified At 2033, 20211201

#include "controller.h"
#include "game.h"
#include "observer.h"
#include "textDisplay.h"
#include "graphicDisplay.h"
#include <iostream>
#include <iomanip>

Controller::Controller() {}   // end constructor 

void Controller::createModel(const std::string& boardType) {
    model = std::make_unique<Game>(boardType);
}   // end createModel

void Controller::createView(const bool isGraphical) {
    Game* g = model.get();
    if(isGraphical)     {
        view.emplace_back(GraphicDisplay(*g));
    } else {
        view.emplace_back(TextDisplay(*g));
    }
}   // end createView

void Controller::acceptInput(const std::string& input) {
    try{
        if (input == "setup") {
            if(model.get()) model->setup(); // if a model already exists
            // after setup, notify the observers to render the whole chess board
            std::vector<std::unique_ptr<Observer>>::iterator it;
            for(it = view.begin(); it != view.end(); it++) {
                Observer* ptr = it->get();
                ptr->notify();
            }
        } else if (input == "resign") {
            model->resign();    // current player resign from this match
        } else if (input == "undo") {

        } else if (input == "move") {
            
        } else if (input == "game") {
            int count = 0;
            std::string aLine, str;
            std::getline(std::cin, aLine);
            std::stringstream ss {aLine};
            
            while(ss >> str) {
                model->setPlayer(count);
                // White -> Black -> Red -> Blue
                int difficulty;
                try {
                    difficulty = std::stoi(str.back());
                } catch(const std::invalid_argument& ia) {
                    difficulty = 1;         // difficulty will be set to 1 by default
                }
                setPlayer(count, str == "human", str.back());
                if(count == 4) {  
                    // identify which four-player board is going to be used
                    if(str == "regular" || str == "r") {
                        throw "Cannot use a two-player board for four players!";
                    } else if (str == "extended" || str == "e") {
                        createModel(str);
                    } else if (str == "corner" || str == "c") {
                        createModel(str);
                    } else {
                        throw "Unrecognized four-hand chess board type!";
                    }
                } else if (count == 5 && (str == "g" || str == "graphical")) 
                    createView(true);
                count ++;
            }   // end while loop
            createView(false);    // attach a textObserver by default
        } else if (input == "help") {
            std::cout << "Available commands:" << std::endl;
            std::cout << std::left << std::setw(10) <<"game" << std::endl;
            std::cout << std::left << std::setw(10) <<"move" << std::endl; 
            std::cout << std::left << std::setw(10) <<"setup" << std::endl;
            std::cout << std::left << std::setw(10) <<"resign" << std::endl;
            std::cout << std::left << std::setw(10) <<"undo" << std::endl;
        } else {
            std::cout << "Unrecognized Command! Type in \"help\" for all valid commands." << std::endl;
        }   // end command selection (if-else statement)
    } catch (std::string& err) {
        throw std::runtime_error{err};
    }   // end try-catch block
}   // end acceptInput