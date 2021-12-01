// Kunling Yang, 20912628
// Last Modified At 2359 20211129

#include "moveHistory.h"

MoveHistory::MoveHistory( const int& maxUndo  ) : maxUndos{ maxUndo }  { }
// end constructor


void MoveHistory::add ( const int &originalX, const int &originalY, 
    const int &finalX, const int &finalY, const char &operation ) {
    mh.emplace( mh.begin(), std::make_unique<Move>( originalX, originalY, finalX, 
        finalY, operation) );
    if ( (int)mh.size() > maxUndos * 2 ) {
        mh.pop_back();
    }
}   // end add

std::vector<Move *> MoveHistory::undo() {
    std::vector<Move *> undos;
    undos.emplace_back( mh[0].release() );
    mh.erase( mh.begin() );
    undos.emplace_back( mh[0].release() );
    mh.erase( mh.begin() );
    return undos;
}   // end undo

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

bool MoveHistory::MoveHistIter::operator!=( const MoveHistIter &it ) {
    return curr == it.curr && mh == mh;
}