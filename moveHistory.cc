// Kunling Yang, 20912628
// Last Modified At (UTC-5) 2259,20211207

#include "moveHistory.h"
#include "limits.h"

MoveHistory::MoveHistory() { }
// end constructor


void MoveHistory::add ( const int &originalX, const int &originalY, 
    const int &finalX, const int &finalY, Board &b ) {
    std::cerr << "add a piece of move hist @ Line 12, moveHistory.cc" << std::endl;
    mh.emplace_back( 
        std::make_unique<Move>( b, originalX, originalY, finalX, finalY ) );
}   // end add

std::vector<Move *> MoveHistory::undo() {
    std::cerr << "undo @ Line21, moveHistory.cc" << std::endl;
    std::vector<Move *> undos;
    undos.emplace_back( mh[0].release() );
    mh.pop_back();
    undos.emplace_back( mh[0].release() );
    mh.pop_back();
    return undos;
}   // end undo

Move *MoveHistory::lastMove() { return mh.back().get(); }

bool MoveHistory::hasMoved() { return mh.size() >= 1; }

void MoveHistory::clearHistory() { mh.clear(); }

MoveHistory::MoveHistIter::MoveHistIter( const int &index, 
    std::vector<std::unique_ptr<Move>> &mh ) : 
    curr{ index }, mh{ mh } { }

MoveHistory::MoveHistIter MoveHistory::begin()  {
    return MoveHistIter{ (int)mh.size() - 1, mh };
}   // end begin

MoveHistory::MoveHistIter MoveHistory::end()   {
    return MoveHistIter{ -1, mh };
}   // end end

Move &MoveHistory::MoveHistIter::operator*()    {
    return *( mh[curr].get() );
}   // end operator*

MoveHistory::MoveHistIter &MoveHistory::MoveHistIter::operator++() {
    curr--;
    return *this;
}

MoveHistory::MoveHistIter &MoveHistory::MoveHistIter::operator--() {
    curr++;
    return *this;
}

bool MoveHistory::MoveHistIter::operator!=( const MoveHistIter &it ) {
    return curr != it.curr || mh != mh;
}
