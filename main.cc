// Kunling Yang, 20912628
// Last Modified At 1929,20211201

#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<Controller> c;
    std::string input;

    while(std::cin >> input) {
        if(std::cin.fail() || input == "quit") {
            c->acceptInput("quit");
            break;
        }   // end if
        try {
            c->acceptInput(input);
        }   catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
}   // end main