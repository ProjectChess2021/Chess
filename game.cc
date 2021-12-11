#include "game.h"
#include <sstream>
#include <iostream>
#include "isChecked.h"
using std::endl;
using std::cout;

void Game::boardInit() {
    mh->clearHistory();
    if ( isSetup ) {
        for ( int i = 0; i < 8; ++i ) {
            for ( int k = 0; k < 8; ++k ) {
                board[i][k] = setUpBoard[i][k];
            }
        }
        return;
    }
    for ( int k = 0; k < 8; ++k ) {
        pieces.emplace_back( std::make_unique<Pawn>( 1 ) );
        board[k][1] = pieces.back().get();
    }
    pieces.emplace_back( std::make_unique<Rook>( 1 ) );
    board[0][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 1 ) );
    board[1][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 1 ) );
    board[2][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Queen>( 1 ) );
    board[3][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<King>( 1 ) );
    board[4][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 1 ) );
    board[5][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 1 ) );
    board[6][0] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Rook>( 1 ) );
    board[7][0] = pieces.back().get();
    for ( int k = 0; k < 8; ++k ) {
        pieces.emplace_back( std::make_unique<Pawn>( 2 ) );
        board[k][6] = pieces.back().get();
    }
    pieces.emplace_back( std::make_unique<Rook>( 2 ) );
    board[0][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 2 ) );
    board[1][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 2 ) );
    board[2][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Queen>( 2 ) );
    board[3][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<King>( 2 ) );
    board[4][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Bishop>( 2 ) );
    board[5][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Knight>( 2 ) );
    board[6][7] = pieces.back().get();
    pieces.emplace_back( std::make_unique<Rook>( 2 ) );
    board[7][7] = pieces.back().get();
    whiteStart = true;
}

Game::Game() :  mh{ std::make_unique<MoveHistory>() }, whiteStart{ true }, isSetup{false} {
    board.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    boardInit();
}

std::string Game::move( const int &originalX, const int &originalY, 
    const int &endX, const int &endY ) {
    Piece *pc =  board[originalX][originalY];
    int side = board[originalX][originalY]->getSide();
    std::string retval = "";

    // The case when piece is going to kill another piece
    if ( board[endX][endY] != nullptr ) {
        deadPool.emplace_back( board[endX][endY] );
        board[originalX][originalY] = nullptr;
        board[endX][endY] = pc;
        retval = "k";
    } else {
        board[endX][endY] = pc;
        board[originalX][originalY] = nullptr;
        retval = "m";
    }

    // Checking pawn capture en passant
    if ( pc->getType() == 'p' && mh->hasMoved() ) {
        Move *lastMove = mh->lastMove();
        Posn *lastMoveEnd = lastMove->getEnd();
        Posn *lastMoveBegin = lastMove->getOriginal();
        Piece *lastPiece = board[lastMoveEnd->getX()][lastMoveEnd->getY()];
        if ( lastPiece->getType() == 'p' ) {
            if ( side == 1 ) {
                if ( endX == lastMoveEnd->getX() && 
                     endY - 1 == lastMoveEnd->getY() &&
                     endX == lastMoveBegin->getX() && 
                     endY + 1 == lastMoveBegin->getY() &&
                     lastPiece->getSide() != pc->getSide() ) {
                    retval = "k";
                }
            } else if ( side == 2 ) {
                if ( endX == lastMoveEnd->getX() && 
                     endY + 1 == lastMoveEnd->getY() &&
                     endX == lastMoveBegin->getX() && 
                     endY - 1 == lastMoveBegin->getY() &&
                     lastPiece->getSide() != pc->getSide() ) {
                    retval = "k";
                }
            }
        }
    }

    // Now checking if this is a promotion
    if ( pc->getType() == 'p' ) {
        if ( endY == 7 || endY == 0 ) {
            char promptTo = 'a';
            while ( true ) {
                cout << "Your pawn is being granted a promotion" << endl;
                cout << "You can change your pawn into:" << endl;
                cout << "(r)ook" << endl;
                cout << "k(n)ight" << endl;
                cout << "(b)ishop" << endl;
                cout << "(q)ueen" << endl;
                std::cin >> promptTo;
                if ( promptTo == 'r' ) {
                    pieces.emplace_back( std::make_unique<Rook>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'n' ) {
                    pieces.emplace_back( std::make_unique<Knight>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'b' ) {
                    pieces.emplace_back( std::make_unique<Bishop>( pc->getSide() ) );
                    break;
                } else if ( promptTo == 'q' ) {
                    pieces.emplace_back( std::make_unique<Queen>( pc->getSide() ) );
                    break;
                }
            }
            deadPool.emplace_back( pc );
            board[endX][endY] = pieces.back().get();
            pieces.back().get()->changeMoved( true );
            if ( retval == "k" ) {
                retval += "+p";
            } else {
                retval = "p";
            }
        }
    }

    // Now check for castling
    if ( pc->getType() == 'k' ) {
        int diffX = endX - originalX;
        if ( diffX == 2 || diffX == -2 ) {
            if ( diffX == 2 ) {
                board[endX][endY] = pc;
                board[originalX][originalY] = nullptr;
                board[endX - 1][endY] = board[7][endY];
                board[endX - 1][endY]->changeMoved( true );
                board[7][endY] = nullptr; 
            } else {
                board[endX][endY] = pc;
                board[originalX][originalY] = nullptr;
                board[endX + 1][endY] = board[0][endY];
                board[0][endY] = nullptr; 
                board[endX + 1][endY]->changeMoved( true );
            }
            retval = "c";
        }
    }

    return retval;
}

void Game::undo() {
    std::vector<Move *> undoHist = mh->undo();
    for ( auto hist : undoHist ) {
        Posn *end = hist->getEnd();
        Posn *begin = hist->getOriginal();
        int endX = end->getX();
        int endY = end->getY();
        int beginX = begin->getX();
        int beginY = begin->getY();
        if ( hist->getOperation() == "m" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "c" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( false );
            if ( endX > beginX ) {
                board[7][endY] = board[endX - 1][endY];
                board[7][endY]->changeMoved( false );
                board[endX - 1][endY] = nullptr;
            } else {
                board[0][endY] = board[endX + 1][endY];
                board[0][endY]->changeMoved( false );
                board[endX + 1][endY] = nullptr;
            }
        } else if ( hist->getOperation() == "k" ) {
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = nullptr;
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        } else if ( hist->getOperation() == "k+p" ) {
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY] = board[endX][endY];
            board[endX][endY] = deadPool.back();
            deadPool.pop_back();
            board[beginX][beginY]->changeMoved( hist->isFirstMove() );
        }
    }
}

void goOn() {
    std::string str = "";
    std::cout << "Press any key to continue: ";
    std::cin >> str;
}

void Game::start() {
    boardInit();
    bool end = false;
    notifyObservers( *this );
    int diffI = 1;
    int diffK = 0;
    if ( !whiteStart ) {
        diffK = -1;
        diffI = 0;
    }
    while ( !end ) {
        for ( int i = 0, k = 1; i < 2 && k >= 0; ) {
            Player *player = nullptr;
            if ( whiteStart ) {
                player = players[i];
            } else {
                player = players[k];
            }
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
                if ( i == 0 ) {
                    cout << "Checkamte! Black wins!" << endl;
                    player[1].getScore()++;
                    end = true;
                } else {
                    cout << "Checkamte! White wins!" << endl;
                    player[0].getScore()++;
                }
                goOn();
                end = true;
                break;
            } else if ( player->hasAvaliableMove() && 
                IsChecked::isChecked( player->getId(), board ) ) {
                if ( i == 0 ) {
                    cout << "White is in check." << endl;
                } else {
                    cout << "Black is in check." << endl;
                }
                goOn();
            }

            std::cerr << __LINE__ << endl;
            std::string cmd = player->cmd( *this );
            
            if ( cmd == "undo" ) {
                i -= diffI; 
                k -= diffK;
                undo();
                player->usedUndo();
            } else if ( cmd == "resign" ) {
                if ( i == 0 ) {
                    cout << "Black wins!" << endl;
                    player[1].getScore()++;
                } else {
                    cout << "White wins!" << endl;
                    player[0].getScore()++;
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
                std::string op = move( iniX, iniY, endX, endY );
                mh->add( iniX, iniY, endX, endY, player->getId(), op, 
                    board[endX][endY]->isMoved() );
                board[endX][endY]->changeMoved( true );
            }
            notifyObservers( *this );
            i += diffI; 
            k += diffK;
        }
    }
}

void errorMsg() {
    cout << "Bad input. You can try:" << endl;
    cout << "+ K e1" << endl;
    cout << "- e1" << endl;
    cout << "= white" << endl;
    cout << "done" << endl;
    cout << "Please enter command here: ";
}

void Game::setup() {
    int whiteKingNum, blackKingNum;
    whiteKingNum = blackKingNum = 0;
    std::string in = "";
    setUpBoard.clear();
    setUpBoard.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    board.clear();
    board.resize( 8, std::vector<Piece *>( 8, nullptr ) );
    pieces.clear();
    notifyObservers(*this);
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
                notifyObservers(*this);
                errorMsg();
                continue;
            }

            char x = 'a';
            int y = 0;
            cmd >> x;
            cmd >> y;
            if ( x < 'a' || x > 'h' || y < 1 || y > 8 ) {
                pieces.pop_back();
                notifyObservers(*this);
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
                board[x - 'a'][y - 1] = pieces.back().get();
                setUpBoard[x - 'a'][y - 1] = pieces.back().get();
            }
        } else if ( op == "-" ) {       // remove a piece
            char x = 'a';
            int y = 0;
            cmd >> x;
            cmd >> y;
            if ( x < 'a' || x > 'h' || y < 1 || y > 8 ) {   // bad Position
                notifyObservers(*this);
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
                        board[x - 'a'][y - 1] = nullptr;
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
                notifyObservers(*this);
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
                notifyObservers(*this);
                prompt += "Invalid Setup. Please replace pieces accordingly.\nPlease enter command here: ";
                cout << prompt;
                continue;
            }
        }   else {  // unrecognized command
            notifyObservers(*this);
            errorMsg();
            continue;
        }//end command selection
        notifyObservers(*this);
        prompt += "Continue to enter command here: ";
        cout << prompt;
    }   // end while
}   // end setup

std::vector<std::vector<Piece *>> &Game::getBoard() { return board; }

MoveHistory *Game::getMoveHistory() { return mh.get(); }

float Game::getScore( int idx ) { return players[idx]->getScore(); }

void Game::addPlayer( Player *player ) { 
    players.emplace_back( player ); 
    attach( player );
}

// This function returns true if the setup is valid, false ow.
bool Game::isValidSetup(const int whiteKingNum, const int blackKingNum, std::string& prompt) {
    std::cerr << "Goes here At " << __LINE__ << " at "<<__FILE__<<endl;
    bool whiteKing = false;
    bool blackKing = false;
    // check the number of king
    if (whiteKingNum > 1)   prompt += "Multiple white kings detected.\n";
        else if (whiteKingNum < 1)  prompt += "No white king detected.\n";
        else whiteKing = true;
    if (blackKingNum > 1)   prompt += "Multiple black kings detected.\n";
        else if (blackKingNum < 1)  prompt += "No black king detected.\n";
        else blackKing = true;
    
    std::cerr << "Debug at Line " << __LINE__ << " from " << __FILE__ << ": " <<
        whiteKingNum << " " << blackKingNum << std::endl;
    
    bool hasInvalidPawn = false;    // check whether there is pawn on the first/last row
    for( int i = 0; i < 2; i++) {
        for ( int j = 0; j < 7; j++ ) {
            if (board[i * 7][j] && board[i * 7][j]->getType() == 'p' ) {
                notifyObservers(*this);
                prompt +="Pawns cannot be placed at the first or last row of the board.\n";
                hasInvalidPawn = true;
                break;
            }
        }   // end inner for loop
    }   // end outer for loop

    bool inCheck = false;   // check if any player is in check
    if ( IsChecked::isChecked( 1, board ) ) {
        notifyObservers(*this);
        prompt += "White king is being checked.\n";
        inCheck = true;
    } else if ( IsChecked::isChecked( 2, board ) ) {
        notifyObservers(*this);
        prompt += "Black king is being checked.\n";
        inCheck = true;
    }   // end if-else statement
    
    return whiteKing && blackKing && !hasInvalidPawn && !inCheck;
}   // end isValidSetup

std::vector<Player*>& Game::getPlayers() {
    return players;
}   // end getPlayers