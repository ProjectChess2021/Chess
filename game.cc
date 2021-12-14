#include "game.h"
#include <sstream>
#include <iostream>
#include "isChecked.h"
using std::endl;
using std::cout;

void Game::boardInit() {
    mh->clearHistory();
    b->boardInit( isSetup );
}

Game::Game() :  mh{ std::make_unique<MoveHistory>() }, 
    b{ std::make_unique<Board>() },
    whiteStart{ true }, isSetup{false} {
    boardInit();
}

void Game::move( const int &originalX, const int &originalY, 
    const int &endX, const int &endY, const int id ) {

    // std::vector<std::vector<Piece *>> board = b->getBoard();
    // Piece *pc =  board[originalX][originalY];
    // int side = board[originalX][originalY]->getSide();
    // std::string retval = "";
    // // The case when piece is going to kill another piece
    // if ( board[endX][endY] != nullptr ) {
    //     b->kill( originalX, originalY, endX, endY );
    //     retval = "k";
    // } 
    // // Checking pawn capture en passant
    // if ( pc->getType() == 'p' && mh->hasMoved() ) {
    //     Move *lastMove = mh->lastMove();
    //     Posn *lastMoveEnd = lastMove->getEnd();
    //     Posn *lastMoveBegin = lastMove->getOriginal();
    //     Piece *lastPiece = board[lastMoveEnd->getX()][lastMoveEnd->getY()];
    //     if ( lastPiece->getType() == 'p' ) {
    //         if ( side == 1 ) {
    //             if ( endX == lastMoveEnd->getX() && 
    //                  endY - 1 == lastMoveEnd->getY() &&
    //                  endX == lastMoveBegin->getX() && 
    //                  endY + 1 == lastMoveBegin->getY() &&
    //                  lastPiece->getSide() != pc->getSide() ) {
    //                 b->CEP( originalX, originalY, endX, endY );
    //                 std::cerr << "Performed CEP" << std::endl;
    //                 retval = "k";
    //             }
    //         } else if ( side == 2 ) {
    //             if ( endX == lastMoveEnd->getX() && 
    //                  endY + 1 == lastMoveEnd->getY() &&
    //                  endX == lastMoveBegin->getX() && 
    //                  endY - 1 == lastMoveBegin->getY() &&
    //                  lastPiece->getSide() != pc->getSide() ) {
    //                 b->CEP( originalX, originalY, endX, endY );
    //                 std::cerr << "Performed CEP" << std::endl;
    //                 retval = "k";
    //             }
    //         }
    //     }
    // }
    // // Now checking if this is a promotion
    // if ( pc->getType() == 'p' ) {
    //     if ( endY == 7 || endY == 0 ) {
    //         char promptTo = 'a';
    //         while ( true ) {
    //             cout << "Your pawn is being granted a promotion" << endl;
    //             cout << "You can change your pawn into:" << endl;
    //             cout << "(r)ook" << endl;
    //             cout << "k(n)ight" << endl;
    //             cout << "(b)ishop" << endl;
    //             cout << "(q)ueen" << endl;
    //             std::cout << "Please enter command here: ";
    //             std::cin >> promptTo;
    //             if ( promptTo == 'r' || promptTo == 'n' || 
    //                 promptTo == 'b' || promptTo == 'q' ) {
    //                 break;
    //             }
    //         }
    //         b->promotion( originalX, originalY, endX, endY, promptTo );
    //         if ( retval == "k" ) {
    //             retval += "+p";
    //         } else {
    //             retval = "p";
    //         }
    //     }
    // }
    // // Now check for castling
    // if ( pc->getType() == 'k' ) {
    //     int diffX = endX - originalX;
    //     if ( diffX == 2 || diffX == -2 ) {
    //         b->castle( originalX, originalY, endX, endY );
    //         retval = "c";
    //     }
    // }  
    // if ( board[endX][endY] == nullptr && retval == "" ) {
    //     std::cerr << __LINE__ << std::endl;
    //     b->move( originalX, originalY, endX, endY );
    //     retval = "m";
    // }

    // return retval;

    mh->add( originalX, originalY, endX, endY, *b );
    char promptTo = 'q';
    Move *last = mh->lastMove();
    if ( last->getOperation() == "p" || 
        last->getOperation() == "k+p" ) {

        promptTo = players[id]->promptTo();
    }
    b->smart_move( *last, promptTo );
}

void Game::undo() {
    std::vector<Move *> undoHist = mh->undo();
    b->undo( undoHist );
}

void Game::goOn() {
    std::string str = "";
    std::cout << std::endl;
    std::cout << "Current score is:" << std::endl;
    std::cout << "White: " << getScore( 0 ) << std::endl;
    std::cout << "Black: " << getScore( 1 ) << std::endl;
    std::cout << "Type in anything and then press [enter] to continue: ";
    std::cin >> str;
}

void Game::start() {
    boardInit();
    bool end = false;
    std::vector<std::vector<Piece *>> &board = b->getBoard();
    notifyObservers( board, *mh );
    int diffI = 1;
    int i = 0;
    while ( !end ) {
        if ( !whiteStart ) {
            //std::cerr << __LINE__ << std::endl;
            diffI = -1;
            i = 1;
        } else {
            diffI = 1;
            i = 0;
        }
        for ( ; i < 2 && i >= 0; ) {
            Player *player = nullptr;
            player = players[i];
            if ( !player->hasAvaliableMove() && 
                !IsChecked::isChecked( player->getId(), board ) ) {
                cout << "Stalemate!" << endl;
                players[0]->getScore() += 0.5;
                players[1]->getScore() += 0.5;
                end = true;
                goOn();
                break;
            } else if ( !player->hasAvaliableMove() && 
                IsChecked::isChecked( player->getId(), board ) ) {
                if ( player->getId() == 1 ) {
                    cout << "Checkamte! Black wins!" << endl;
                    for ( int i = 0; i < (int)players.size(); ++i ) {
                        if ( players[i]->getId() == 2 ) {
                            players[i]->getScore()++;
                        }
                    }
                } else {
                    cout << "Checkamte! White wins!" << endl;
                    for ( int i = 0; i < (int)players.size(); ++i ) {
                        if ( players[i]->getId() == 1 ) {
                            players[i]->getScore()++;
                        }
                    }
                }
                goOn();
                end = true;
                break;
            } else if ( player->hasAvaliableMove() && 
                IsChecked::isChecked( player->getId(), board ) ) {
                if ( player->getId() == 1 ) {
                    cout << "White is in check." << endl;
                } else {
                    cout << "Black is in check." << endl;
                }
            }
            std::string cmd = player->cmd( *this );
            
            if ( cmd == "undo" ) {
                if ((mh.get())->size() < 2) {
                    i -= diffI;
                    cout << "There is nothing in the move histroy to undo." << endl;
                } else {
                    i -= diffI; 
                    undo();
                    player->usedUndo();
                }
            } else if ( cmd == "resign" ) {
                if ( i == 0 ) {
                    cout << "Black wins!" << endl;
                    players[1]->getScore()++;
                } else {
                    cout << "White wins!" << endl;
                    players[0]->getScore()++;
                }
                goOn();
                end = true;
                break;
            } else if ( cmd == "" ) {
                end = true;
                break;
            } else {
                std::stringstream in{ cmd };
                std::string str = "";
                std::string iniPosn = "";
                std::string endPosn = "";
                in >> str;
                in >> iniPosn;
                in >> endPosn;
                int iniX = iniPosn[0] - 'a';
                int iniY = iniPosn[1] - '1';
                int endX = endPosn[0] - 'a';
                int endY = endPosn[1] - '1';
                move( iniX, iniY, endX, endY, i );
            }
            notifyObservers( board, *mh );
            std::cerr << __LINE__ << std::endl;
            i += diffI; 
        }
    }
}

void errorMsg() {
    cout << "Unrecognized setup command is detected. You can try:" << endl;
    cout << "  \"+ K e1\"   (which puts a white King at e1)" << endl;
    cout << "  \"- e1\"     (which removes a piece from e1 if any)" << endl;
    cout << "  \"= white\"  (which set white takes the next move after applying setup)." << endl;
    cout << "  \"done\"     (which detects if it's a valid setup and applies it to following games if success." << endl;
    cout << "Please enter command here: ";
}

void Game::setup() {
    int whiteKingNum, blackKingNum;
    whiteKingNum = blackKingNum = 0;
    b->getPieces().clear();
    b->getSetUpBoard().clear();
    std::string in = "";
    std::vector<std::unique_ptr<Piece>> &pieces = b->getPieces();
    std::vector<std::vector<Piece *>> &setUpBoard = b->getSetUpBoard();
    setUpBoard.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    notifyObservers( setUpBoard, *mh );
    cout << "Please enter command here: ";
    while( std::getline( std::cin, in ) ) {
        std::string op = "";
        std::string prompt = "";
        std::stringstream cmd{ in };
        cmd >> op;
        if ( op == "+" ) {
            char pc = '1';
            cmd >> pc;
            if ( pc == 'r' ) {
                pieces.emplace_back( std::make_unique<Rook>( 2 ) );
            } else if ( pc == 'R' ) {
                pieces.emplace_back( std::make_unique<Rook>( 1 ) );
            } else if ( pc == 'n' ) {
                pieces.emplace_back( std::make_unique<Knight>( 2 ) );
            } else if ( pc == 'N' ) {
                pieces.emplace_back( std::make_unique<Knight>( 1 ) );
            } else if ( pc == 'b' ) {
                pieces.emplace_back( std::make_unique<Bishop>( 2 ) );
            } else if ( pc == 'B' ) {
                pieces.emplace_back( std::make_unique<Bishop>( 1 ) );
            } else if ( pc == 'q' ) {
                pieces.emplace_back( std::make_unique<Queen>( 2 ) );
            } else if ( pc == 'Q' ) {
                pieces.emplace_back( std::make_unique<Queen>( 1 ) );
            } else if ( pc == 'k' ) {
                blackKingNum ++;    // a new blackKing is added
                pieces.emplace_back( std::make_unique<King>( 2 ) );
            } else if ( pc == 'K' ) {
                whiteKingNum ++;    // a new whiteKing is added
                pieces.emplace_back( std::make_unique<King>( 1 ) );
            } else if ( pc == 'p' ) {
                pieces.emplace_back( std::make_unique<Pawn>( 2 ) );
            } else if ( pc == 'P' ) {
                pieces.emplace_back( std::make_unique<Pawn>( 1 ) );
            } else {
                notifyObservers( setUpBoard, *mh );
                errorMsg();
                continue;
            }

            char x = 'a';
            int y = 0;
            cmd >> x;
            cmd >> y;
            if ( x < 'a' || x > 'h' || y < 1 || y > 8 ) {
                if ( pieces.back()->getType() == 'k' ) {
                    if ( pieces.back()->getSide() == 1 ) {
                        whiteKingNum--;
                    } else {
                        blackKingNum--;
                    }
                }
                pieces.pop_back();
                notifyObservers( setUpBoard, *mh );
                errorMsg();
                continue;
            }
            if ( setUpBoard[x - 'a'][y - 1] != nullptr &&
                pieces.back()->getType() == 'k' &&
                setUpBoard[x - 'a'][y - 1]->getType() == 'k' && 
                pieces.back()->getSide() == setUpBoard[x - 'a'][y - 1]->getSide() ) {
                prompt += "Nothing changed \n";
                if ( pieces.back()->getSide() == 1 ) {
                    whiteKingNum--;
                } else {
                    blackKingNum--;
                }
                pieces.pop_back();
            } else {
                prompt += "Add piece successful.\n";
                setUpBoard[x - 'a'][y - 1] = pieces.back().get();
            }
        } else if ( op == "-" ) {       // remove a piece
            char x = 'a';
            int y = 0;
            cmd >> x;
            cmd >> y;
            if ( x < 'a' || x > 'h' || y < 1 || y > 8 ) {   // bad Position
                notifyObservers( setUpBoard, *mh );
                errorMsg();
                continue;
            }
            //board[x - 'a'][y - 1] = pieces.back().get();
            if(setUpBoard[x - 'a'][y - 1] == nullptr) {
                prompt += "No piece is detected there. Remove nothing.\n";
            }   else {
                std::vector<std::unique_ptr<Piece>>::iterator it;
                for(it = pieces.begin(); it != pieces.end(); ++it){
                    Piece* piecePtr = it->get();
                    if(piecePtr == setUpBoard[x - 'a'][y - 1]) {  //find the right pointer
                        if(piecePtr->getType() == 'k') {          // a king is to be removed
                            if(piecePtr->getSide() == 1) whiteKingNum--;          // white king removed
                            else if(piecePtr->getSide() == 2) blackKingNum--;     // black king removed
                        }
                        setUpBoard[x - 'a'][y - 1] = nullptr;    // remove from board
                        pieces.erase(it);                   // remove from pieces list
                        prompt += "Remove piece successful.\n";
                        break;
                    }
                }   // end for loop to track piece to be removed
            }   // end if-else on where a piece is there    
        } else if ( op == "=" ) {
            std::string side = "";
            cmd >> side;
            if ( side == "white" || side == "black" ) {
                whiteStart = (side == "white");
            } else {
                notifyObservers( setUpBoard, *mh );
                errorMsg();
                continue;
            }
        } else if ( op == "done" ) {
            std::string prompt = "";
            if(isValidSetup(whiteKingNum,blackKingNum,prompt)){
                prompt += "Setup completed and will take effect in next game";
                isSetup = true;
                break;
            } else {
                notifyObservers( setUpBoard, *mh );
                prompt += "Invalid Setup. Please replace pieces accordingly.\nPlease enter command here: ";
                cout << prompt;
                continue;
            }
        }   else {  // unrecognized command
            notifyObservers( setUpBoard, *mh );
            errorMsg();
            continue;
        }//end command selection
        notifyObservers( setUpBoard, *mh );
        prompt += "Continue to enter command here: ";
        if ( op == "=" ) {
            if ( whiteStart ) {
                std::cout << "White will make the next move." << std::endl;
            } else {
                std::cout << "Black will make the next move." << std::endl;
            }
        }
        cout << prompt;
    }   // end while
}   // end setup

std::vector<std::vector<Piece *>> &Game::getBoard() { return b->getBoard(); }

Board& Game::getb() {return *b;}

MoveHistory *Game::getMoveHistory() { return mh.get(); }

float Game::getScore( int idx ) { 
    if ( players.size() > 1 )
        return players[idx]->getScore(); 
    else
        return 0;
}

void Game::addPlayer( Player *player ) { 
    players.emplace_back( player ); 
    attach( player );
}

void Game::clearPlayer() { 
    for ( int i = 0; i < (int)players.size(); ++i ) {
        detach( players[i] );
    }
    players.clear(); 
}

// This function returns true if the setup is valid, false ow.
bool Game::isValidSetup(const int whiteKingNum, const int blackKingNum, std::string& prompt) {
    bool whiteKing = false;
    bool blackKing = false;

    std::vector<std::vector<Piece *>> board = b->getSetUpBoard();
    // check the number of king
    if (whiteKingNum > 1)   prompt += "Multiple white kings detected.\n";
        else if (whiteKingNum < 1)  prompt += "No white king detected.\n";
        else whiteKing = true;
    if (blackKingNum > 1)   prompt += "Multiple black kings detected.\n";
        else if (blackKingNum < 1)  prompt += "No black king detected.\n";
        else blackKing = true;
    
    bool hasInvalidPawn = false;    // check whether there is pawn on the first/last row
    for( int i = 0; i < 8; i += 7) { // only check first row and last row
        for ( int j = 0; j < 8; j++ ) {
            if (board[j][i] && board[j][i]->getType() == 'p' ) {
                notifyObservers( board, *mh );
                prompt +="Pawns cannot be placed at the first or last row of the board.\n";
                hasInvalidPawn = true;
                break;
            }
        }   // end inner for loop
    }   // end outer for loop

    bool inCheck = false;   // check if any player is in check
    if ( IsChecked::isChecked( 1, board ) ) {
        notifyObservers( board, *mh );
        prompt += "White king is being checked.\n";
        inCheck = true;
    } else if ( IsChecked::isChecked( 2, board ) ) {
        notifyObservers( board, *mh );
        prompt += "Black king is being checked.\n";
        inCheck = true;
    }   // end if-else statement
    
    return whiteKing && blackKing && !hasInvalidPawn && !inCheck;
}   // end isValidSetup

std::vector<Player*>& Game::getPlayers() {
    return players;
}   // end getPlayers

Player* Game::nextPlayer(int currId) {
    Player* retPtr = nullptr;
    for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++){
        if((*it)->getId() == currId) {  // locate current player
            it++;
            if(it == players.end())     // currPlayer is the last player
                retPtr = *(players.begin());
            else    retPtr = *it;
            break;
        }
    }
    return retPtr;
}   //end nextPlayer