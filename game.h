// Kunling Yang, 20912628
// Last Modified At 0007, 20211201

#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <memory>
#include "posn.h"
#include "subject.h"
#include "moveHistory.h"
#include "piece.h"

class Player;

class Game : public Subject {
    std::vector<int> score;     // store the score for each player
    std::vector<Player *> players;
    std::unique_ptr<MoveHistory> mh;
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<std::vector<Piece *>> board;
    std::vector<Piece *> deadPool;
    int boardSize;
    int currPlayerIdx;
    std::string boardType;  // one of "regular", "extended", "corner"

  public: 
    Game( std::vector<Player *> *players, const std::string& boardType);
    // Use board and movehistory in start, which is in each game
    char move( Posn *original, Posn *end );
    char undo( Posn *end, Posn *original );
    void setup();
    int getBoardSize() noexcept;
    std::string getBoardType() noexcept;
    std::vector<std::vector<Piece *>>& getBoard();
    std::unique_ptr<MoveHistory> getMoveHistory();
    int getScore(int idx);  // return the currentScore of a single player
    int resign();           // current Player resign
    void setPlayer(const int id, bool isHuman, int difficultyLV);
    // void mutateBoard(); //potentially want to change the board after a match?
};  // end Game

#endif
