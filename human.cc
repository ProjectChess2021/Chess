#include "human.h"
#include <string>
#include "game.h"
#include "isChecked.h"
#include <iostream>
#include "king.h"
#include <vector>

Human::Human( const int &_id, const float score ) : 
    Player{ _id, score } { }

std::string Human::valid( const int &iniX, const int &iniY, const int &endX, 
    const int &endY, Game &g ) {
    Posn init{ iniX, iniY };
    Posn end{ endX, endY };
    if ( iniX < 0 || iniX >= 8 ||  iniY < 0 || iniY >= 8)
        return "Provided move start is outside board boundry!";
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8 ) 
        return "Provided move destination is outside board boundry!";

    std::vector<std::vector<Piece *>>& board = g.getBoard();
    if ( !board[iniX][iniY] ) return "No piece detected at the start position";
    if ( board[iniX][iniY]->getSide() != getId() )
        return "Attempt to move an opponent-controlled piece";    
    if ( board[iniX][iniY]->getType() == 'p' && std::abs(iniY - endY) == 2 &&
            iniX == endX && board[iniX][iniY]->isMoved())
        return "A pawn can only advancing two steps in its first move";
    if( board[iniX][iniY]->getType() == 'k' && std::abs(iniX - endX) == 2 &&
            iniY == endY && (board[iniX][iniY]->isMoved() ||
            ((iniX - endX) == 2 && board[0][iniY]->getType() == 'r' && board[0][iniY]->isMoved())   ||  // move left and thta rook is already moved
            ((iniX - endX) == -2 && board[7][iniY]->getType() == 'r' && board[7][iniY]->isMoved())))    // move right and that rook is already moved
        return "Invalid Castling, both king and rook must be unmoved";
    if ( !board[iniX][iniY]->isValidMove( &init, &end, 
            board, g.getMoveHistory() ) )
            return "Provided move is illegal!";

    return "";
}

std::string Human::cmd( Game &game ) {
    std::string cmd = "";
    std::string iniPosn = "";
    std::string endPosn = "";
    std::vector<std::vector<Piece *>> board = game.getBoard();

    std::cout << "Please enter command here: ";

    while ( std::cin >> cmd ) {
        Move* _move = nullptr;      // used to generate prompts
        if(getAM().size()) _move = getAM().at(rand() % getAM().size()).get();
        if ( cmd == "move" ) {
            int iniX, iniY, endX, endY;
            std::cin >> iniPosn;
            std::cin >> endPosn;
            iniX = iniPosn[0] - 'a';
            iniY = iniPosn[1] - '1';
            endX = endPosn[0] - 'a';
            endY = endPosn[1] - '1';
            
            std::string ret = valid( iniX, iniY, endX, endY, game );
            
            if ( ret.length() ) {
                std::cout << ret << std::endl;
                std::cout << "If You do not know which piece to move, try " << *_move->getOriginal() << std::endl;
                std::cout << "Please enter command here: ";
                continue;
            }

            if ( IsChecked::isCheckMove( 
                iniX, iniY, endX, endY, getId(), board ) ) {
                std::cout << "Your king will be exposed to enemy capture if taking that move" << std::endl;
                std::cout << "Please reconsider next move and enter command here: ";
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
                std::cout << "You have used up all of your undos. Other available commands are: " << std::endl;
                if(!_move)  
                    std::cout << "    \"move e1 e8\" (which moves a piece owned by you)" << std::endl;
                else{
                    std::cout << "    \"move " << *(_move->getOriginal()) << " "
                    << *(_move->getEnd()) <<"\"  (which moves a piece owned by you)" << std::endl;
                }
                std::cout << "    \"resign\"      (which allows you to quit and add one score for the opponent)" << std::endl;
                std::cout << "Please enter command here: ";
                continue;
            }
            //return cmd;
        } else {
            std::cout << "Unrecognized command detected!" << std::endl;
        }

        std::cout << "Possible command templates are listed below: " << std::endl;
        std::cout << "    \"move " << *(_move->getOriginal()) << " "
            << *(_move->getEnd()) <<"\"  (which moves a piece owned by you)" << std::endl;
        std::cout << "    \"resign\"      (which allows you to quit and add one score for the opponent)"<< std::endl;
        if ( getNumUndo() < 0 ) {
            std::cout << "    \"undo\"        (which allows you to undo last movement of both sides)" << std::endl;
        } else if (getNumUndo() > 0){
            std::cout << "    \"undo\"       (which allows you to undo last movement of both sides)" << std::endl;
            std::cout << "                   (there are still " << getNumUndo() << " times of undo availables)" << std::endl;
        } else {
            std::cout << "    \"undo\"       (There is no undo availale now)" << std::endl;
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
