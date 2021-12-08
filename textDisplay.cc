// Kunling Yang, 20912628
// Last Modified At 1840,20211201

#include "textDisplay.h"
#include <iostream>
#include "moveHistory.h"
#include <iomanip>

// Initialize the Board as a blank board.
TextDisplay::TextDisplay(Game& g) : g{g} {
    int occupy = (8 - 1) * (8 - 1);
    display.resize(occupy, std::vector<char>(occupy, ' '));
}  // end Constructor

// update the TextObserver once get notified
void TextDisplay::notify() {
    std::cerr << "begin notify() @ Line 26, textDisplay.cc" << std::endl;
    std::vector<std::vector<Piece*>> aBoard = g.getBoard();
    for(int i = 0; i < (int)aBoard.size(); i++) {
        for(int j = 0; j < (int)aBoard[i].size(); j++) {
            if(aBoard[i][j])        // not nullptr, there is piece on [i][j]
                display[i][j] = aBoard[i][j]->getType();
            else display[i][j] =  (i + j ) % 2 ? ' ' : '_';
        }   // end inner for loop
    }   // end outer for loop
}   // end notify

// This function returns the Board as ostream
std::ostream &operator<<(std::ostream & out, const TextDisplay& txtOb) {
    std::cerr << "Operator<< @ Line 39, textDisplay.cc" << std::endl;
    //system("clear");          // clear what's on the screen so it looks nicer
    std::unique_ptr<MoveHistory> MHptr = txtOb.g.getMoveHistory();
    int displayNum = 0;               // the number of moveHistory piece to be displayed
    MoveHistory::MoveHistIter it = MHptr->end();
    while(displayNum <= 4 && it != MHptr->begin()) { // Only newest five moves (at most) will be displayed
        --it;
        displayNum ++;
    }
    for(int i = 7; i >= 0; i--) {
        out << i + 1 << " ";       // Line Num
        for(int j = 0; j < (int)txtOb.display[i].size(); j++){
                out << txtOb.display[i][j];
        }    // end inner for loop 
        out << "      ";
        // There are still Move History pieces to be displayed:
        if(i == 7)  out << "MoveHistory";
        else if(displayNum > 0 && it != MHptr->end()) {
            out << *it;
            ++it;
            displayNum--;
        }
        out << std::endl;
    }   //end outer for loop
    out << std::endl << "  ";
    for(int i = 0; i < 8; i ++) out<<(char)( 'a' + i);
    system("pause");
    return out;
}   // end operator<<
