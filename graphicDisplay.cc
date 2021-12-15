#include "graphicDisplay.h"
#include <iostream>
const int W2 = 1;
const int B2 = 1;
const int E = 1;

// This function draws a Pawn at the center of given side at given area
// Try to give a even sqaure?
void GraphicDisplay::drawPawn(const int x, const int y, const int side) {
    if(d[x][y] == 'p' && side == 2) return;
    if(d[x][y] == 'P' && side == 1) return;

    // int edgex = 3 - 1;
    // int edgey = 10 - 1;
}   // end drawPawn

GraphicDisplay::GraphicDisplay( const int width, const int height ) :
    width{ width }, height{ height }, 
    display{ std::make_unique<Xwindow>( 50 * width + 70,
                                        50 * height + 70 ) } {
    d.resize( width, std::vector<char>( height, ' ' ) );
    display->fillRectangle( 25, 25, 50 * width + 20, 50 * width + 20, 4 );
    for ( int k = 0; k < 8; ++k ) {
        std::string s = "a";
        s[0] += k;
        display->drawString( 60 + 50 * k, 15, s );
    }

    for ( int k = 0; k < 8; ++k ) {
        std::string s = "a";
        s[0] += k;
        display->drawString( 60 + 50 * k, 460, s );
    }

    for ( int k = 0; k < 8; ++k ) {
        std::string s = "8";
        s[0] -= k;
        display->drawString( 10, 65 + 50 * k, s );
    }

    for ( int k = 0; k < 8; ++k ) {
        std::string s = "8";
        s[0] -= k;
        display->drawString( 455, 65 + 50 * k, s );
    }

    display->fillRectangle( 35, 35, 400, 400, 2 );

    for ( int i = 0; i < 8; ++i ) {
        for ( int k = 0; k < 8; ++k ) {
            if ( ( i + k ) % 2 == 1 )
                display->fillRectangle( 
                    35 + 50 * i, 35 + 50 * k, 50, 50, 3 );
        }
    }
}

void GraphicDisplay::notify( std::vector<std::vector<Piece *>> &b, 
    MoveHistory &mh ) {
    for ( int k = 0; k < 8; ++k ) {
        for ( int i = 0; i < 8; ++i ) {
            if ( d[i][k] != ' ' && b[i][ 7 - k] == nullptr ) {
                if ( ( i + k ) % 2 == 1 )
                    display->fillRectangle( 
                        35 + 50 * i, 35 + 50 * k, 50, 50, 3 );
                else
                    display->fillRectangle( 
                        35 + 50 * i, 35 + 50 * k, 50, 50, 2 );
            } else if ( b[i][7 - k] ) {
                if ( b[i][7 - k]->getType() != d[i][k] ) {
                    std::string s = " ";
                    d[i][k] = b[i][7 - k]->getType();
                    if ( b[i][7 - k]->getSide() == 1 ) {
                        s[0] = d[i][k] - 'a' + 'A';
                        display->drawString( 60 + 50 * i, 65 + 50 * k, s );
                    } else {
                        s[0] = d[i][k];
                        display->drawString( 60 + 50 * i, 65 + 50 * k, s );
                    }
                }
            }
        }
    }
}

GraphicDisplay::~GraphicDisplay() { }
