// Kunling Yang, 20912628
// Last Modified At 1821, 20211124

// #include "game.h"
// #include "player.h"
// //#include "window.h"
// #include <iostream>
// #include <memory>

// int main() {
//     std::unique_ptr<Game> aGame;
//     std::string command;

//     while(std::cin >> command) {
//         if(std::cin.fail() || command == "quit") {
//             aGame.display();
//             break;
//         }   
//         if (command == "game"){
//             std::string p1;
//             std::string p2;
//             std::cin >> p1 >> p2;
//             aGame.setup(p1, p2);
//         else if (command == "resign") {
//             aGame.end();
//         } else if (command == "setup") {


//         } else {

//             std::cout << "Unrecognized command!" << std::endl;
//         }
//     }
// }