// Kunling Yang, 20912628
// Last Modified At 2359 20211129

#include "moveHistory.h"

MoveHistory::MoveHistory( const int& maxUndo) :
    maxUndos{maxUndos}  {}
// end constructor


void MoveHistory::add (const Move& mv)   {
    std::unique_ptr<Move> movePtr = std::make_unique<Move>(mv);
    mh.emplace(mh.begin(), mv);
}   // end add

Move& MoveHistory::undo()    {
}   // end undo


MoveHistory::MoveHistIter& MoveHistory::begin()  {
    return MoveHistIter{0};
}   // end begin

MoveHistory::MoveHistIter& MoveHistory::end()   {
    return MoveHistIter{mh.length()};
}   // end end

Move& MoveHistory::MoveHistIter::operator*()    {
    return mh.at(curr);
}   // end operator*

