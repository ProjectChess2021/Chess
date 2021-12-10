// Created by Zichu
// Last Modifed At 1840,20211201 (By Kunling Yang)
#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "move.h"
#include "moveHistory.h"
#include <vector>
#include "posn.h"
#include "game.h"
#include "game.h"

class TextDisplay : public Observer {
    std::vector<Move*> displayHistory;
    std::vector<std::vector<char>> displayBoard; // Holds the occupy status of the whole board
    public:
    TextDisplay();
    ~TextDisplay() = default;
    virtual void notify(Game& game) override;
    friend std::ostream &operator<<( std::ostream &, TextDisplay& );
    std::vector<Move*>* getDisplayHist();
};

#endif
