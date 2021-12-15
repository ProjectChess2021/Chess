// Kunling Yang, 20912628
// Last Modified At 1840,20211201

#include "textDisplay.h"
#include <iostream>
#include <iomanip>

// This function prints a lot of newline character as if SYS("clear")
void clear(){
    for(int i = 0; i < 20; i ++)    std::cout << std::endl;
}   // end screenClear()

// Initialize the Board as a blank board.
TextDisplay::TextDisplay() {
    int occupy = 8 * 8;
    displayBoard.resize(occupy, std::vector<char>(occupy, ' '));
}  // end Constructor

// update the TextObserver once get notified
void TextDisplay::notify( std::vector<std::vector<Piece *>>& b, MoveHistory &mh ) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(b[i][j])        // not nullptr, there is piece on [i][j]
                if (b[i][j]->getSide() == 1 ) {
                    displayBoard[i][j] = b[i][j]->getType() - 'a' + 'A';
                } else {
                    displayBoard[i][j] = b[i][j]->getType();
                }
            else displayBoard[i][j] =  (i + j ) % 2 ? ' ' : '_';
        }   // end inner for loop
    }   // end outer for loop

    // extract last five moves (at most)
    displayHistory.clear();
    MoveHistory* MHptr = &mh;
    int displayNum = 0;               // the number of moveHistory piece to be displayed
    MoveHistory::MoveHistIter it = MHptr->begin();
    while(displayNum < 8 && it != MHptr->end()) {       // display 5 pieces at most
        displayNum ++;
        displayHistory.emplace_back(&(*it));
        ++it;
    }
    std::cout << *this << std::endl;
}   // end notify

// This function translates the side number to a string (colour representing the player)
std::string getSideStr(const int x){
    if(x == 1)     return "white";
    else if(x == 2) return "black";
    else if(x == 3) return "azure";
    else if(x == 4) return "green";
    else return "";
}   // end getSideStr

// This function returns the Board as ostream
std::ostream &operator<<(std::ostream & out, TextDisplay& txtOb) {
    clear();        // clear what's on the screen so it looks nicer
    std::vector<Move*>& hist = txtOb.displayHistory;
    std::vector<Move*>::iterator it = hist.begin();

    for(int i = 7; i >= 0; i--) {
        out << i + 1 << " ";       // Line Num
        for(int j = 0; j < (int)txtOb.displayBoard[i].size(); j++) // print cells
                out << txtOb.displayBoard[j][i];
        out << " ";

        if(i == 7)  out << "Move History (Newest at top)";
        else if(it != hist.end()) {
            std::string sideStr = getSideStr((*it)->getSide());
            sideStr[0] = toupper(sideStr[0]);
            out << "        " << sideStr << ": " <<  *(*it);
            ++it;
        }
        out << std::endl;
    }   //end outer for loop
    out << std::endl << "  ";
    for(int i = 0; i < 8; i ++) out<<(char)( 'a' + i);
    return out;
}   // end operator<<
