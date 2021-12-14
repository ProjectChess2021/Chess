#include "human.h"
#include <string>
#include "game.h"
#include "isChecked.h"
#include <iostream>
#include "king.h"
#include <vector>

Human::Human( const int &_id, const float score ) : 
    Player{ _id, score } { }

bool Human::valid( const int &iniX, const int &iniY, const int &endX, 
    const int &endY, Game &g ) {
    Posn init{ iniX, iniY };
    Posn end{ endX, endY };
    if ( iniX < 0 || iniX >= 8 ) return false;
    if ( iniY < 0 || iniY >= 8 ) return false;
    if ( endX < 0 || endX >= 8 ) return false;
    if ( endY < 0 || endY >= 8 ) return false;
    std::vector<std::vector<Piece *>> board = g.getBoard();
    if ( board[iniX][iniY] == nullptr ) return false;
    if ( !board[iniX][iniY]->isValidMove( &init, &end, 
            board, g.getMoveHistory() ) ) return false;
    if ( board[iniX][iniY]->getSide() != getId() ) return false;
    return true;
}

std::string Human::cmd( Game &game ) {
    std::string cmd = "";
    std::string iniPosn = "";
    std::string endPosn = "";
    std::vector<std::vector<Piece *>> board = game.getBoard();

    std::cout << "Please enter command here: ";

    while ( std::cin >> cmd ) {
        if ( cmd == "move" ) {
            std::cin >> iniPosn;
            std::cin >> endPosn;
            int iniX = iniPosn[0] - 'a';
            int iniY = iniPosn[1] - '1';
            int endX = endPosn[0] - 'a';
            int endY = endPosn[1] - '1';

            if ( !valid( iniX, iniY, endX, endY, game ) ) {
                std::cout << "Invalid coordinates" << std::endl;
                std::cout << "Please enter command here: ";
                continue;
            }

            std::cerr << "iniX = " << iniX << std::endl;
            std::cerr << "iniY = " << iniY << std::endl;
            std::cerr << "endX = " << endX << std::endl;
            std::cerr << "endY = " << endY << std::endl;

            if ( IsChecked::isCheckMove( 
                iniX, iniY, endX, endY, getId(), board ) ) {
                std::cout << "Your king will be checked by this move" << std::endl;
                std::cout << "Please think carefully before you make your move" << std::endl;
                std::cout << "Please enter command here: ";
                continue;
            } else { 
                return cmd + " " + iniPosn + " " + endPosn;
            }

        } else if ( cmd == "resign" ) {
            return cmd;
        } else if ( cmd == "undo" ) {
            if ( getNumUndo() != 0 ) {
                return cmd;
            } else {
                std::cout << "You have used out your undos" << std::endl;
            }
            return cmd;
        } else {
            std::cout << "Invalid command!" << std::endl;
        }

        std::cout << "Command template: " << std::endl;
        std::cout << "move e1 e8" << std::endl;
        std::cout << "resign" << std::endl;
        if ( getNumUndo() <= 0 ) {
            std::cout << "undo(0)" << std::endl;
        } else {
            std::cout << "undo(" << getNumUndo() << ")" << std::endl;
        }
        std::cout << "Please enter command here: ";
    }

    return cmd;
}

char Human::promptTo() {
    char prom = 'q';
    std::cout << "Your pawn is being granted a promotion" << std::endl;
    std::cout << "You can change your pawn into:" << std::endl;
    std::cout << "(r)ook" << std::endl;
    std::cout << "k(n)ight" << std::endl;
    std::cout << "(b)ishop" << std::endl;
    std::cout << "(q)ueen" << std::endl;
    while ( true ) {
        std::cout << "Please enter command here: ";
        std::cin >> prom;
        if ( prom == 'r' || prom == 'n' || 
            prom == 'b' || prom == 'q' ) {
            break;
        } else {
            std::cout << "Invalid promotion!" << std::endl;
        }
    }
    return prom;
}

// test case
// int main() {
//     Human h{ 1 };
//     std::vector<std::vector<Piece *>> board;
//     for ( int i = 0; i < 8; ++i ) {
//         std::vector<Piece *> col;
//         for ( int k = 0; k < 8; ++k ) {
//             col.emplace_back( nullptr );
//         }
//         board.emplace_back( col );
//     }

//     board[5][5] = new King{ 1 };
//     std::cout << h.cmd( board ) << std::endl;;
// }