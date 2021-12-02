// Created by Zichu
// Last Modifed At 1840,20211201 (By Kunling Yang)
#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "game.h"
#include <vector>
#include "posn.h"

class TextDisplay : public Observer {
    Game &g;
    std::vector<std::vector<char>> display; // Holds the occupy status of the whole board
    bool isInExtendedBoard(const int, const int) noexcept;  // return true if it is a valid posn on Extended Board
    bool isInExtendedBoard(Posn&) noexcept;            
    bool isInRegularBoard(const int, const int) noexcept;  // return true if it is a valid posn on Extended Board
    bool isInRegularBoard(Posn&) noexcept;  
    bool isInCornerBoard(const int, const int) noexcept;  // return true if it is a valid posn on Extended Board
    bool isInCornerBoard(Posn&) noexcept;  
    public:
    TextDisplay( Game &g );
    ~TextDisplay() override;

    void notify() override;

    friend std::ostream &operator<<( std::ostream &, const TextDisplay& );
};

#endif