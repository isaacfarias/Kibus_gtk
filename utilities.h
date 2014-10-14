#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "cell.h"

cell* bresenham_next_cell(cell a,cell b)
{
    int xa = a.x, ya = a.y, xb = b.x, yb = b.y;
    int x, y, dx, dy, inc_x, inc_y, p;
    dx= abs(xb-xa);
    dy= abs(yb-ya);
    x= xa;
    y= ya;

    if(xa>xb)
      {
        inc_x= -1;
      }
    else
        {

          inc_x= 1;
        }
    if(ya>yb)
      {

        inc_y= -1;
      }
    else
        {
          inc_y= 1;
        }

    if(dx>=dy)
      {
        p= dx/2;
        if (x!=xb)
             {
               p= p-dy;
               if(p<0)
                 {
                   y= y+inc_y;
                   p= p+dx;
                 }
               x += inc_x;
               return new cell(x,y); //glVertex2f(x,y); //
             }
      }
    else
        if(dy>dx)
           {
             p= dy/2;
             if (y!=yb)
                   {
                     p= p-dx;
                     if(p<0)
                       {
                         x= x+inc_x;
                         p= p+dy;
                       }
                     y= y+inc_y;
                    return new cell(x,y); //glVertex2f(x,y);
                   }
           }

}
#endif // UTILITIES_H_INCLUDED
