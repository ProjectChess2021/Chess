// Kunling Yang, 20912628
// Last Modified At 2314, 20211130

#include "textDisplay.h"
#include <iostream>
#include <iomanip>

// Initialize the Board as a blank board.
TextDisplay::TextDisplay(Game& g) : g{g}, size{g.getPlayerNum() == 2 ? 8 : 14} {
    int occupy = (size - 1) * (size - 1);
    display.resize(occupy, std::vector<char>(occupy, ' '));
}  // end Constructor

// This function returns true if this is a valid cell on a FourHandBoard
bool withInFourHandBoard(const int x, const int y) {
    return  (x <= 2 && y <= 2) || (x <= 2 && y >= 11) ||
            (x >= 11 && y <= 2) ||  (x >= 11 && y >= 11);
}   // end isBeyondFourHandBoard

// update the TextObserver once get notified
void TextDisplay::notify() override {
    std::vector<std::vector<Piece*>> aBoard = g.getBoard();
    for(int i = 0; i < aBoard.size(); i++) {
        for(int j = 0; j < aBoard[i].size(); j++) {
            if(aBoard[i][j])        // not nullptr, there is piece on [i][j]
                display[i][j] = aBoard[i][j]->getType();
            else {
                if(g.getPlayerNum() == 2)   display[i][j] =  (i + j ) % 2 ? ' ' : '_';
                else {              // four-hand chess
                    if(withInFourHandBoard(i,j))    display[i][j] =  (i + j ) % 2 ? '_' : ' ';
                    else display[i][j] = 'X';
                }
            }
        }   // end inner for loop
    }   // end outer for loop
}   // end notify

// This function returns the Board as ostream
std::ostream &operator<<(std::ostream & out, const TextDisplay& txtOb) {
    system("clear");          // clear what's on the screen so it looks nicer
    for(int i = 0; i < txtOb.display.size(); i++) {
        out <<std::left << std::setw(2) << txtOb.size - i << " ";       // Line Num
        for(int j = 0; j < txtOb.display[i].size(); j++){
                out << txtOb.display[i][j];
        }    // end inner for loop 
        out << std::endl;
    }   //end outer for loop
    out << std::endl;
    for(int i = 0; i < txtOb.size; i ++) out<<(char)( 'a' + 0);
    system("pause");
}   // end operator<<
