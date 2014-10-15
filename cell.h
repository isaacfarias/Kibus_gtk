#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class cell
{
    public:
        int x,y,v;
        cell(int xa, int ya)
        {
            x = xa;
            y = ya;
        }
        cell(int xa, int ya,int va)
        {
            x = xa;
            y = ya;
            v = va;
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
        bool operator <(const cell &b)
        {
            return this->v < b.v;
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
    cout<<"Cell: "<<x<<", "<<y<<", "<<v<<endl;
}
    protected:
    private:
};


#endif // CELL_H
