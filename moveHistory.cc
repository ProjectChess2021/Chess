// Kunling Yang, 20912628
// Last Modified At 2359 20211129

#include "moveHistory.h"

MoveHistory::MoveHistory( const int& maxUndo ) : maxUndos{ maxUndos }  { }
// end constructor


void MoveHistory::add ( const int &originalX, const int &originalY, 
    const int &finalX, const int &finalY, const char &operation ) {
    mh.emplace( mh.begin(), std::make_unique<Move>( originalX, originalY, finalX, 
        finalY, operation) );
    if ( mh.size() > maxUndos * 2 ) {
        mh.pop_back();
    }
}   // end add

std::unique_ptr<Move> MoveHistory::undo() {
    std::unique_ptr<Move> mv = std::move( mh[0] );
    mh.erase( mh.begin() );
    return std::move( mv );
}   // end undo

MoveHistory::MoveHistIter::MoveHistIter( const int &index ) : 
    curr{ index }, mh{ mh } { }

MoveHistory::MoveHistIter MoveHistory::begin()  {
    return MoveHistIter{ 0 };
}   // end begin

MoveHistory::MoveHistIter MoveHistory::end()   {
    return MoveHistIter{ mh.size() };
}   // end end

Move &MoveHistory::MoveHistIter::operator*()    {
    return *( mh[curr].get() );
}   // end operator*

MoveHistory::MoveHistIter &MoveHistory::MoveHistIter::operator++() {
    curr++;
    return *this;
}