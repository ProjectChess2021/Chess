#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "game.h"
#include <vector>

class TextDisplay : public Observer {
    Game &g;
    std::vector<std::vector<char>> display;
    public:
    TextDisplay( Game &g );
    ~TextDisplay() override;

    void notify() override;

    friend std::ostream &operator<<( std::ostream &, const TextDisplay& );
};

#endif