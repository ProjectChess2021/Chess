#ifndef __ISCHECKED_H__
#define __ISCHECKED_H__

class IsChecked {
    public:
    bool static isChecked( const int &x, const int &y, const int &side,
    std::vector<std::vector<Piece *>> &board );
};

#endif