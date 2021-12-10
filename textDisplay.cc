// Kunling Yang, 20912628
// Last Modified At 1840,20211201

#include "textDisplay.h"
#include <iostream>
#include <iomanip>

// Initialize the Board as a blank board.
TextDisplay::TextDisplay() {
    int occupy = 8 * 8;
    displayBoard.resize(occupy, std::vector<char>(occupy, ' '));
}  // end Constructor

// update the TextObserver once get notified
void TextDisplay::notify(Game& _g) {
    std::cerr << "begin notify() @ Line 26, textDisplay.cc" << std::endl;
    std::vector<std::vector<Piece*>>& aBoard = _g.getBoard();
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(aBoard[i][j])        // not nullptr, there is piece on [i][j]
                displayBoard[i][j] = aBoard[i][j]->getType();
            else displayBoard[i][j] =  (i + j ) % 2 ? ' ' : '_';
        }   // end inner for loop
    }   // end outer for loop

    // extract last five moves (at most)
    displayHistory.clear();
    MoveHistory* MHptr = _g.getMoveHistory();
    int displayNum = 0;               // the number of moveHistory piece to be displayed
    MoveHistory::MoveHistIter it = MHptr->begin();
    while(displayNum < 5 && it != MHptr->end()) {       // display 5 pieces at most
        displayNum ++;
        displayHistory.emplace_back(&(*it));
        ++it;
    }
}   // end notify

std::vector<Move*>* TextDisplay::getDisplayHist() {
    return &displayHistory;
}   // end getDisplayHist()

// This function returns the Board as ostream
std::ostream &operator<<(std::ostream & out, TextDisplay& txtOb) {
    std::cerr << "Operator<< @ Line 39, textDisplay.cc" << std::endl;
    //system("clear");          // clear what's on the screen so it looks nicer
    auto histptr = txtOb.getDisplayHist();
    std::vector<Move*>::iterator it = histptr->begin();

    for(int i = 7; i >= 0; i--) {
        out << i + 1 << " ";       // Line Num
        for(int j = 0; j < (int)txtOb.displayBoard[i].size(); j++){
                out << txtOb.displayBoard[i][j];
        }    // end inner for loop 
        out << "      ";

        if(i == 7)  out << "MoveHistory";
        else if(it != histptr->end()) {
            out << *it;
            ++it;
        }
        out << std::endl;
    }   //end outer for loop
    out << std::endl << "  ";
    for(int i = 0; i < 8; i ++) out<<(char)( 'a' + i);
    //system("pause");
    return out;
}   // end operator<<
