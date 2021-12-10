// Kunling Yang, 20912628
// Last Modified At (UTC-5) 2259,20211207

#include "moveHistory.h"

MoveHistory::MoveHistory( const int& maxUndo  ) : maxUndos{ maxUndo }  { }
// end constructor


void MoveHistory::add ( const int &originalX, const int &originalY, 
    const int &finalX, const int &finalY, const int& side, const std::string &operation, 
    const bool &firstMove ) {
    std::cerr << "add a piece of move hist @ Line 12, moveHistory.cc" << std::endl;
    mh.emplace( mh.begin(), std::make_unique<Move>( originalX, originalY, finalX, 
        finalY, side, operation, firstMove) );
    if ( (int)mh.size() > maxUndos * 2 ) {
        mh.pop_back();
    }
}   // end add

std::vector<Move *> MoveHistory::undo() {
    std::cerr << "undo @ Line21, moveHistory.cc" << std::endl;
    std::vector<Move *> undos;
    undos.emplace_back( mh[0].release() );
    mh.erase( mh.begin() );
    undos.emplace_back( mh[0].release() );
    mh.erase( mh.begin() );
    return undos;
}   // end undo

Move *MoveHistory::lastMove() { return mh[0].get(); }

bool MoveHistory::hasMoved() { return mh.size() >= 1; }

MoveHistory::MoveHistIter::MoveHistIter( const int &index, 
    std::vector<std::unique_ptr<Move>> &mh ) : 
    curr{ index }, mh{ mh } { }

MoveHistory::MoveHistIter MoveHistory::begin()  {
    return MoveHistIter{ 0, mh };
}   // end begin

MoveHistory::MoveHistIter MoveHistory::end()   {
    return MoveHistIter{ (int)mh.size(), mh };
}   // end end

Move &MoveHistory::MoveHistIter::operator*()    {
    return *( mh[curr].get() );
}   // end operator*

MoveHistory::MoveHistIter &MoveHistory::MoveHistIter::operator++() {
    curr++;
    return *this;
}

MoveHistory::MoveHistIter &MoveHistory::MoveHistIter::operator--() {
    curr--;
    return *this;
}

bool MoveHistory::MoveHistIter::operator!=( const MoveHistIter &it ) {
    return curr != it.curr || mh != mh;
}
