#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class cell
{
    public:
        int x,y;
        cell(int xa, int ya)
        {
            x = xa;
            y = ya;
        }
        virtual ~cell() {}
        bool operator == (const cell &b)
{
    return ((this->x == b.x) && (this->y == b.y));
}
    protected:
    private:
};


#endif // CELL_H
