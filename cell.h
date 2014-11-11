#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class cell
{
    public:
        int x,y,v;
        int extra_data;
        cell(int xa, int ya)
        {
            x = xa;
            y = ya;
            extra_data = 0;
        }
        cell(int xa, int ya,int va)
        {
            x = xa;
            y = ya;
            v = va;
            extra_data = 0;
        }
        virtual ~cell() {}
        bool operator <=(const cell &b)
        {
            return this->v <= b.v;
        }
        bool operator >=(const cell &b)
        {
            return this->v >= b.v;
        }

        bool operator >(const cell &b)
        {
            return this->v > b.v;
        }
        bool operator == (const cell &b)
{
    return ((this->x == b.x) && (this->y == b.y));
}
void to_string()
{
    //cout<<"Cell: "<<x<<", "<<y<<", "<<v<<endl;
}
    protected:
    private:
};

bool operator <(const cell &a,const cell &b)
        {
            return a.v < b.v;
        }


#endif // CELL_H
