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
            //cout<<x<<" "<<y<<endl;
        }
        virtual ~cell() {}
    protected:
    private:
};

#endif // CELL_H
