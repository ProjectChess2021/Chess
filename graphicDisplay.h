#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "observer.h"
#include <memory>
#include "window.h"
#include "game.h"
#include <vector>
#include "piece.h"

class GraphicDisplay : public Observer {
    int width;
    int height;
    std::unique_ptr<Xwindow> display;
    std::vector<std::vector<char>> d;
    public:
    GraphicDisplay( const int width, const int height );
    ~GraphicDisplay();

    void notify( std::vector<std::vector<Piece *>> &b, 
        MoveHistory &mh ) override;
};

#endif