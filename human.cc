#include "human.h"
#include <string>
#include "isChecked.h"
#include <iostream>
#include "king.h"
#include <vector>

Human::Human( const int &side ) : Player{ side } { }

bool inRange( const int &iniX, const int &iniY, const int &endX, const int &endY ) {
    if ( iniX < 0 || iniX >= 8 ) {
        return false;
    }
    if ( iniY < 0 || iniY >= 8 ) {
        return false;
    }
    if ( endX < 0 || endX >= 8 ) {
        return false;
    }
    if ( endY < 0 || endY >= 8 ) {
        return false;
    }
    return true;
}

std::string Human::cmd( std::vector<std::vector<Piece *>> board ) {
    std::string cmd = "";
    std::string iniPosn = "";
    std::string endPosn = "";
    int kingX = 0;
    int kingY = 0;

    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( board[i][k] != nullptr ) {
                if ( board[i][k]->getType() == 'k' ) {
                    if ( board[i][k]->getSide() == getId() ) {
                        kingX = i;
                        kingY = k;
                    }
                }
            }
        }
    }

    while ( true ) {
        std::cout << "Please enter command here: ";
        std::cin >> cmd;
        if ( cmd == "move" ) {
            std::cin >> iniPosn;
            std::cin >> endPosn;
            int iniX = iniPosn[0] - 'a';
            int iniY = iniPosn[1] - '1';
            int endX = endPosn[0] - 'a';
            int endY = endPosn[1] - '1';

            if ( !inRange( iniX, iniY, endX, endY ) ) {
                std::cout << "Invalid coordinates" << std::endl;
                continue;
            }

            Posn init{ iniX, iniY };
            Posn end{ endX, endY };

            std::cerr << "iniX = " << iniX << std::endl;
            std::cerr << "iniY = " << iniY << std::endl;
            std::cerr << "endX = " << endX << std::endl;
            std::cerr << "endY = " << endY << std::endl;

            if ( board[iniX][iniY]->isValidMove( &init, &end, board ) ) {
                board[endX][endY] = board[iniX][iniY];
                board[iniX][iniY] = nullptr;
            } else {
                std::cout << "Invalid move!" << std::endl;
                continue;
            }

            if ( IsChecked::isChecked( kingX, kingY, getId(), board ) ) {
                std::cout << "Your king will be checked by this move" << std::endl;
                std::cout << "Please think carefully before you make your move" << std::endl;
                continue;
            } else { 
                return cmd + " " + iniPosn + " " + endPosn;
            }

        } else if ( cmd == "resign" ) {
            return cmd;
        } else if ( cmd == "undo" ) {
            return cmd;
        } else {
            std::cout << "Invalid command!" << std::endl;
            std::cout << "Command template: " << std::endl;
            std::cout << "move e1 e8" << std::endl;
            std::cout << "resign" << std::endl;
            std::cout << "undo" << std::endl;
        }   
    }
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