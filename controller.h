// Kunling Yang
// Last Modified At 1825, 20211201

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <memory>
#include <string>
#include <vector>

class Observer;
class Game;

class Controller {
    std::vector<std::unique_ptr<Observer>> view;  // store the ptr to all Observers
    std::unique_ptr<Game> model;
    void createView(const bool) noexcept;     // attach an observer, true if desire a graphical one
    void createModel(const std::string&) noexcept;
    void displayScore() noexcept;
    void notify() noexcept;
    public:
    Controller();
    void acceptInput(const std::string&);
};  // end Controller

#endif
