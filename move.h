// Zichu
// Last Modified At (UTC-5)2254,20211209 (By Kunling)

#ifndef __MOVE_H__ 
#define __MOVE_H__

#include "posn.h"
#include <memory>
#include <vector>
#include <map>

using std::vector;
class Board;
const std::map<char,int> PIECEWEIGHT{
    {'p', 5}, {'r', 25}, {'n', 15}, {'b', 20}, {'q', 100}, {'k', 9999}
};

// credit to Chess-programming-wiki, some modification is applied
const std::map<char, vector<vector<int>>> POSWEIGHT {
    {'p', vector<vector<int>>{     // pawn position weight
        vector<int> {-99,-99,-99,-99,-99,-99,-99,-99},           // 1st Line
        vector<int> {1,  2,  2,  -4, -4, 2,  2,  1},             // 2nd Line
        vector<int> {1,  -1, -2, 0,  0,  -2, -1, 1},             // 3rd Line
        vector<int> {0,  0,  0,  4,  4,  0,  0,  0},             // 4th Line
        vector<int> {1,  1,  2,  5,  5,  2,  1,  1},             // 5th Line
        vector<int> {2,  2,  4,  6,  6,  4,  2,  2},             // 6th Line
        vector<int> {10, 10, 10, 10, 10, 10, 10, 10},            // 7th Line
        vector<int> {50, 50, 50, 50, 50, 50, 50, 50} }},         // 8th Line
    {'r', vector<vector<int>>{      // rook position weight
        vector<int>{0,  0,  1,  1,  1,  1,  0,  0},              // 1st Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 2nd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 3rd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 3rd Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 4th Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 5th Line
        vector<int>{-1, 0,  0,  0,  0,  0,  0,  -1},             // 6th Line
        vector<int>{1,  2,  2,  3,  3,  2,  2,  1},              // 7th Line
        vector<int>{0,  0,  0,  0,  0,  0,  0,  0} }},           // 8th Line
    {'n', vector<vector<int>>{      // knight position weight
        vector<int>{-10, -8, -6, -6, -6, -6, -8, -10},           // 1st Line
        vector<int>{-8, -4, 0,  1,  1,  0,  -4, -8},             // 2nd Line
        vector<int>{-6, 1,  2,  3,  3,  2,  1,  -6},             // 3rd Line
        vector<int>{-6, 0,  3,  4,  4,  3,  0,  -6},             // 4th Line
        vector<int>{-6, 0,  3,  4,  4,  3,  0,  -6},             // 5th Line
        vector<int>{-6, 0,  2,  3,  3,  2,  0,  -6},             // 6th Line
        vector<int>{-8, -4, 0,  1,  1,  0,  -4, -8},             // 7th Line
        vector<int>{-10, -8, -6, -6, -6, -6, -8, -10}}},         // 8th Line
    {'b', vector<vector<int>>{       // Bishop position weight
        vector<int>{-4, -2, -2, -2, -2, -2, -2, -4},             // 1st Line
        vector<int>{-2, 1,  0,  0,  0,  0,  1,  -2},             // 2nd Line
        vector<int>{-2, 2,  2,  2,  2,  2,  2,  -2},             // 3rd Line
        vector<int>{-2, 0,  2,  2,  2,  2,  0,  -2},             // 4th Line
        vector<int>{-2, 1,  1,  2,  2,  1,  1,  -2},             // 5th Line
        vector<int>{-2, 0,  1,  2,  2,  1,  0,  -2},             // 6th Line
        vector<int>{-2, 0,  0,  0,  0,  0,  0,  -2},             // 7th Line
        vector<int>{-4, -2, -2, -2, -2, -2, -2, -4}}},              // 8th Line
    {'q', vector<vector<int>>{      // Queen position weight
        vector<int>{-4, -2, -2, -1, -1, -2, -4},                 // 1st Line
        vector<int>{-2, 0,  1,  0,  0,  0,  0,  -2},             // 2nd Line
        vector<int>{-2, 1,  1,  1,  1,  1,  0,  -2},             // 3rd Line
        vector<int>{0,  0,  1,  1,  1,  1,  0,  -1},             // 4th Line
        vector<int>{-1, 0,  1,  1,  1,  1,  0,  -1},             // 5th Line
        vector<int>{-2, 0,  1,  1,  1,  1,  0,  -2},             // 6th Line
        vector<int>{-2, 0,  0,  0,  0,  0,  0,  -2},             // 7th Line
        vector<int>{-4, -2, -2, -1, -1, -2, -2, -4}}},              // 8th Line
    {'k', vector<vector<int>>{      // King position weight
        vector<int>{4,  6,  2,  0,  0,  2,  6,  4},              // 1st Line
        vector<int>{4,  4,  0,  0,  0,  0,  4,  4},              // 2nd Line
        vector<int>{-2, -4, -4, -4, -4, -4, -4, -2},             // 3rd Line
        vector<int>{-4, -6, -6, -8, -8, -6, -6, -4},             // 4th Line
        vector<int>{-8, -12,-12,-20,-20,-12,-12,-8},             // 5th Line
        vector<int>{-10,-15,-15,-25,-25,-15,-15,-10},            // 6th Line
        vector<int>{-10,-15,-15,-25,-25,-15,-15,-10},            // 7th Line
        vector<int>{-15,-20,-20,-30,-30,-20,-20,-15}}}
};

class Move {
    std::unique_ptr<Posn> original;
    std::unique_ptr<Posn> end;
    int side;
    bool firstMove;
    std::string operation; //(c)astling,(m)ove,(k)ill,(p)romotion
    public:
    Move(Posn&, Posn&, const int&, const std::string&, const bool &firstMove);
    Move( const int &originalX, const int &originalY, const int &finalX, 
        const int &finalY, const int, const std::string operation, 
        const bool _isFirstMove);
    Move(Board&, Posn&, Posn&);
    Move(Board&, const int, const int, const int, const int);

    int getSide();
    Posn* getOriginal();
    Posn* getEnd();
    int getsx();
    int getsy();
    int getex();
    int getey();
    bool isFirstMove();
    std::string getOperation();
    friend std::ostream &operator<<( std::ostream &, const Move& ); 
};

#endif
