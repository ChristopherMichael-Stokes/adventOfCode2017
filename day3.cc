#include <iostream>
#include <cmath>
#include <map>

int part1(const int square)
{
    struct {int x,y,val; } point = { 0, 0, 1 };
    int num = 1;

    for (int sidelength = 3; point.val!=square; sidelength += 2) {
        ++point.x;
        ++point.val;
        for (int i = 0; i < sidelength - 2 && square != point.val; ++i) {
            ++point.val;
            ++point.y;
        } 
        for (int i = 0; i < sidelength - 1 && square != point.val; ++i) {
            ++point.val;
            --point.x;
        }
        for (int i = 0; i < sidelength - 1 && square != point.val; ++i) {
            ++point.val;
            --point.y;
        }
        for (int i = 0; i < sidelength - 1 && square != point.val; ++i) {
            ++point.val;
            ++point.x;
        }
    }
    return abs(point.x)+abs(point.y);
}

typedef struct { int x, y; } point;

int part2(const int val)
{
    int square = 1;
    point p = {0,0};
    std::map<std::pair<int,int>, int> squares;
    squares[std::make_pair(p.x,p.y)] = square;
    ++p.x;
    for (int i = 3; square <= val; i +=2) {
        for (int j = 0; j < i - 1 && square <= val; ++j) {
            std::pair<int,int> labove(p.x-1,p.y+1), lbelow(p.x-1,p.y-1), left(p.x-1,p.y);
            bool _lup, _ldown, _left;
            _lup = (squares.find(labove) != squares.end());
            _ldown = (squares.find(lbelow) != squares.end());
            _left = (squares.find(left) != squares.end());
            if (!_left) {
                square += squares.at(lbelow);
            } else if (!_lup && _ldown) {
                square += squares.at(lbelow)+squares.at(left);
            } else if (!_ldown && _lup) {
                square += squares.at(labove);
            } else if (_lup && _ldown) {
                square += squares.at(labove)+squares.at(lbelow)+squares.at(left);
            }
            squares[std::make_pair(p.x,p.y)] = square;
            ++p.y;
        }
        --p.y; --p.x;
        for (int j = 0; j < i - 1 && square <= val; ++j) {
            std::pair<int, int> dright(p.x+1,p.y-1), dleft(p.x-1,p.y-1), down(p.x,p.y-1);
            bool downright, downleft, _down;
            downright = (squares.find(dright) != squares.end());
            downleft = (squares.find(dleft) != squares.end());
            _down = (squares.find(down) != squares.end());
            if (!_down) {
                square += squares.at(dright);
            } else if (!downleft && downright) {
                square += squares.at(dright)+squares.at(down);
            } else if (!downright && downleft) {
                square += squares.at(dleft)+squares.at(down);
            } else if (downleft && downright) {
                square += squares.at(dleft)+squares.at(dright)+squares.at(down);
            }
            squares[std::make_pair(p.x,p.y)] = square;
            --p.x;
        }
        ++p.x; --p.y;
        for (int j = 0; j < i - 1 && square <= val; ++j) {
            std::pair<int, int> rup(p.x+1,p.y+1), rdown(p.x+1,p.y-1), right(p.x+1,p.y);
            bool _rup, _rdown, _right;
            _rup = (squares.find(rup) != squares.end());
            _rdown = (squares.find(rdown) != squares.end());
            _right = (squares.find(right) != squares.end());
            if (!_right) {
                square += squares.at(rup);
            } else if (!_rup && _rdown) {
                square += squares.at(rdown) + squares.at(right);
            } else if (!_rdown && _rup) {
                square += squares.at(rup) + squares.at(right);
            } else if (_rup && _rdown) {
                square += squares.at(rup)+squares.at(rdown)+squares.at(right);
            }
            squares[std::make_pair(p.x,p.y)] = square;
            --p.y;
        }
        ++p.y; ++p.x;
        for (int j = 0; j < i - 1 && square <= val; ++j) {
            std::pair<int, int> uright(p.x+1,p.y+1), uleft(p.x-1,p.y+1), up(p.x,p.y+1);
            bool _uright, _uleft, _up;
            _uright = (squares.find(uright) != squares.end());
            _uleft = (squares.find(uleft) != squares.end());
            _up = (squares.find(up) != squares.end());
            if (!_up) {
                square += squares.at(uleft);
            } else if (!_uright && _uleft) {
                square += squares.at(uleft)+squares.at(up);
            } else if (!_uleft && _uright) {
                square += squares.at(uright)+squares.at(up);
            } else if (_uleft && _uright) {
                square += squares.at(uleft)+squares.at(uright)+squares.at(up);
            }
            squares[std::make_pair(p.x,p.y)] = square;
            ++p.x;
        }
    }
    //std::cout << '\n';
    //for (const auto& s : squares) {
    //    std::cout << "x y val " << s.first.first << " " << s.first.second << " " << s.second << '\n';
    //}
    return square;
}

int main()
{
    const int input = 361527;
    std::cout << "part1: " << part1(input) << "\tpart2: " << part2(input) << '\n';     
    return 0;
}