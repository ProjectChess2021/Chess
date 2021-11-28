#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "observer.h"
#include <memory>
#include "window.h"
#include "game.h"
#include <vector>

class GraphicDisplay : public Observer {
    Game &g;
    std::unique_ptr<Xwindow> display;
    std::vector<std::vector<char>> d;
    public:
    GraphicDisplay( Game &g );
    ~GraphicDisplay();

    void notify() override;
};

#endif