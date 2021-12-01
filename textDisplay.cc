// Kunling Yang, 20912628
// Last Modified At 1840,20211201

#include "textDisplay.h"
#include <iostream>
#include "moveHistory.h"
#include <iomanip>

// Initialize the Board as a blank board.
TextDisplay::TextDisplay(Game& g) : g{g} {
    int occupy = (g.getBoardSize() - 1) * (g.getBoardSize() - 1);
    display.resize(occupy, std::vector<char>(occupy, ' '));
}  // end Constructor

// This function returns true if this is a valid cell on a FourHandBoard
bool TextDisplay::isInExtendedBoard(const int x, const int y) {
    bool onCorner = (x <= 2 && y <= 2) || (x <= 2 && y >= 11) ||      // Not on four corners
                    (x >= 11 && y <= 2) ||  (x >= 11 && y >= 11);
    return  !onCorner && 0 <= x && x <= 13 && 0 <= y && y <= 13;      // Not outside the boundary
}   // end isInExtendedBoard

bool TextDisplay::isInExtendedBoard(Posn& pos) {
    return isInExtendedBoard(pos.getX(), pos.getY());
}   // end isInExtendedBoard

// This function returns true if this is a valid cell on a Regular Board
bool TextDisplay::isInRegularBoard(const int x, const int y) {
    return 0 <= x && x <= 7 && 0 <= y && y <= 7;
}   // end isInRegularBoard

bool TextDisplay::isInRegularBoard(Posn& pos) {
    return isInRegularBoard(pos.getX(), pos.getY());
}   // end isInRegularBoard

bool TextDisplay::isInCornerBoard(const int x, const int y) {
    return (0 <= x && x <= 12 && 0 <= y && y <= 12);
}   // end isInCornerBoard

bool TextDisplay::isInCornerBoard(Posn& pos) {
    return isInCornerBoard(pos.getX(), pos.getY());
}   // end isInCornerBoard

// update the TextObserver once get notified
void TextDisplay::notify() {
    std::vector<std::vector<Piece*>> aBoard = g.getBoard();
    for(int i = 0; i < (int)aBoard.size(); i++) {
        for(int j = 0; j < (int)aBoard[i].size(); j++) {
            if(aBoard[i][j])        // not nullptr, there is piece on [i][j]
                display[i][j] = aBoard[i][j]->getType();
            else {
                if(g.getBoardType() != "Extended")   display[i][j] =  (i + j ) % 2 ? ' ' : '_';
                else {              // four-hand chess
                    if(isInExtendedBoard(i,j))    display[i][j] =  (i + j ) % 2 ? '_' : ' ';
                    else display[i][j] = 'X';
                }
            }   // end if-else statement
        }   // end inner for loop
    }   // end outer for loop
}   // end notify

// This function returns the Board as ostream
std::ostream &operator<<(std::ostream & out, const TextDisplay& txtOb) {
    system("clear");          // clear what's on the screen so it looks nicer
    std::unique_ptr<MoveHistory> MHptr = txtOb.g.getMoveHistory();
    MoveHistory::MoveHistIter it = MHptr->begin();
    for(int i = 0; i < txtOb.g.getBoardSize(); i++) {
        out <<std::left << std::setw(2) << txtOb.g.getBoardSize() - i << " ";       // Line Num
        for(int j = 0; j < (int)txtOb.display[i].size(); j++){
                out << txtOb.display[i][j];
        }    // end inner for loop 

        // Move History Display:
        if(it != MHptr->end()) {
            out << std::left << std::setw(15) << *it;
            ++it;
        }
        out << std::endl;
    }   //end outer for loop
    out << std::endl;
    for(int i = 0; i < txtOb.g.getBoardSize(); i ++) out<<(char)( 'a' + 0);

    system("pause");
    return out;
}   // end operator<<
