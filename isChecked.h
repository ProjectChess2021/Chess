#ifndef __ISCHECKED_H__
#define __ISCHECKED_H__

#include <vector>
#include "piece.h"

class IsChecked {
    public:
    bool static isChecked( const int &x, const int &y, const int &side,
        std::vector<std::vector<Piece *>>& board );
    bool static isChecked( const int &side,
        std::vector<std::vector<Piece *>>& board );
    bool static isCheckMove(const int, const int, const int, const int, const int,
        std::vector<std::vector<Piece *>>& board);
    bool static canCheckMove(Move&, std::vector<std::vector<Piece*>>&);
    //bool static canCheckMove(Move&, Board&);
};

#endif
