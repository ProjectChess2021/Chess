// Kunling Yang
// Last Modified At (UTC-5) 2114, 20211203

#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include <utility>
#include "move.h"
#include <string>
#include <vector>
#include <map>
#include "game.h"
using std::pair;
using std::vector;

const std::map<char,int> PIECEWEIGHT{
    {'p', 5}, {'r', 25}, {'n', 15}, {'b', 20}, {'q', 100}, {'k', 9999}
};

// credit to Chess-programming-wiki, some modification is applied
const vector<pair<char, vector<vector<int>>>> POSWEIGHT {
    pair<char, vector<vector<int>>>('p', vector<vector<int>> {     // pawn position weight
        vector<int> {-99,-99,-99,-99,-99,-99,-99,-99},           // 1st Line
        vector<int> {1,  2,  2,  -4, -4, 2,  2,  1},             // 2nd Line
        vector<int> {1,  -1, -2, 0,  0,  -2, -1, 1},             // 3rd Line
        vector<int> {0,  0,  0,  4,  4,  0,  0,  0},             // 4th Line
        vector<int> {1,  1,  2,  5,  5,  2,  1,  1},             // 5th Line
        vector<int> {2,  2,  4,  6,  6,  4,  2,  2},             // 6th Line
        vector<int> {10, 10, 10, 10, 10, 10, 10, 10},            // 7th Line
        vector<int> {50, 50, 50, 50, 50, 50, 50, 50}             // 8th Line
    }), pair<char, vector<vector<int>>>('r', vector<vector<int>> { // rook position weight
        vector<int>{0,  0,  0,  1,  1,  0,  0,  0},              // 1st Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 2nd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 3rd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 3rd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 4th Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 5th Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 6th Line
        vector<int>{1,  2,  2,  3,  3,  2,  2,  1},              // 7th Line
        vector<int>{0,  0,  0,  0,  0,  0,  0,  0}               // 8th Line
    }), pair<char, vector<vector<int>>>('n', vector<vector<int>> { // knight position weight
        vector<int>{-10, -8, -6, -6, -6, -6, -8, -10},           // 1st Line
        vector<int>{-8, -4, 0,  1,  1,  0,  -4, -8},             // 2nd Line
        vector<int>{-6, 1,  2,  3,  3,  2,  1,  -6},             // 3rd Line
        vector<int>{-6, 0,  3,  4,  4,  3,  0,  -6},             // 4th Line
        vector<int>{-6, 0,  3,  4,  4,  3,  0,  -6},             // 5th Line
        vector<int>{-6, 0,  2,  3,  3,  2,  0,  -6},             // 6th Line
        vector<int>{-8, -4, 0,  1,  1,  0,  -4, -8},             // 7th Line
        vector<int>{-10, -8, -6, -6, -6, -6, -8, -10}            // 8th Line
    }), pair<char, vector<vector<int>>>('b', vector<vector<int>> {// Bishop position weight
        vector<int>{-4, -2, -2, -2, -2, -2, -2, -4},             // 1st Line
        vector<int>{-2, 1,  0,  0,  0,  0,  1,  -2},             // 2nd Line
        vector<int>{-2, 2,  2,  2,  2,  2,  2,  -2},             // 3rd Line
        vector<int>{-2, 0,  2,  2,  2,  2,  0,  -2},             // 4th Line
        vector<int>{-2, 1,  1,  2,  2,  1,  1,  -2},             // 5th Line
        vector<int>{-2, 0,  1,  2,  2,  1,  0,  -2},             // 6th Line
        vector<int>{-2, 0,  0,  0,  0,  0,  0,  -2},             // 7th Line
        vector<int>{-4, -2, -2, -2, -2, -2, -2, -4}              // 8th Line
    }), pair<char, vector<vector<int>>>('q', vector<vector<int>> { // Queen position weight
        vector<int>{-4, -2, -2, -1, -1, -2, -4},                 // 1st Line
        vector<int>{-2, 0,  1,  0,  0,  0,  0,  -2},             // 2nd Line
        vector<int>{-2, 1,  1,  1,  1,  1,  0,  -2},             // 3rd Line
        vector<int>{0,  0,  1,  1,  1,  1,  0,  -1},             // 4th Line
        vector<int>{-1, 0,  1,  1,  1,  1,  0,  -1},             // 5th Line
        vector<int>{-2, 0,  1,  1,  1,  1,  0,  -2},             // 6th Line
        vector<int>{-2, 0,  0,  0,  0,  0,  0,  -2},             // 7th Line
        vector<int>{-4, -2, -2, -1, -1, -2, -2, -4}              // 8th Line
    }), pair<char, vector<vector<int>>>('k', vector<vector<int>> { // King position weight
        vector<int>{4,  6,  2,  0,  0,  2,  6,  4},              // 1st Line
        vector<int>{4,  4,  0,  0,  0,  0,  4,  4},              // 2nd Line
        vector<int>{-2, -4, -4, -4, -4, -4, -4, -2},             // 3rd Line
        vector<int>{-4, -6, -6, -8, -8, -6, -6, -4},             // 4th Line
        vector<int>{-8, -12,-12,-20,-20,-12,-12,-8},             // 5th Line
        vector<int>{-10,-15,-15,-25,-25,-15,-15,-10},            // 6th Line
        vector<int>{-10,-15,-15,-25,-25,-15,-15,-10},            // 7th Line
        vector<int>{-15,-20,-20,-30,-30,-20,-20,-15}
    })
};

class Strategy {    
    public:
    virtual ~Strategy() = default;
    virtual std::string makeMove(std::vector<std::vector<Piece *>>&, std::vector<Move>&)  = 0;
};  // end Strategy

#endif
