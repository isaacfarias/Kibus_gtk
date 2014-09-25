#ifndef VIRTUAL_FIELD_H
#define VIRTUAL_FIELD_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "cell.h"
using std::cout;
using std::endl;

#define X_MAX 20
#define Y_MAX 15

#define EMPTY        0b0000
#define KIBUS        0b0001
#define OBSTACLE     0b0010
#define CASA         0b0100

#define VIRTUAL_UP 0
#define VIRTUAL_DOWN 1
#define VIRTUAL_LEFT 2
#define VIRTUAL_RIGHT 3
class virtual_field
{
    public:
        int field[Y_MAX][X_MAX];
        cell *kibus_cell;
        cell *casa_cell;
        bool kibus_exist;
        bool home_alone;
        std::vector <cell*> *available_cells;
        std::vector <cell*> *unavailable_cells;
        std::vector <int> *moves;

        virtual_field()
        {
            kibus_cell = new cell(-1,-1);
            home_alone = false;
            casa_cell = NULL;
            kibus_exist = false;
            available_cells = new std::vector<cell*>();
            unavailable_cells = new std::vector<cell*>();
            init_field();
            moves = new std::vector<int>();

            for(int i=0;i<number_of_items(20);i++)
            {
                insert_random();
            }
            //print_cell_vector();
            to_string();
            cout<<available_cells->size()<<endl;
            cout<<unavailable_cells->size()<<endl;
            //number_of_items(20);
        }

        void set_random(int percentage)
        {
            int quantity = number_of_items(percentage);
            int delta = unavailable_cells->size()-quantity;
            if(delta > 0)
                for(int i=0;i<delta;i++)
                {
                    remove_random();
                }
            if(delta < 0)
                for(int i=0;i<(delta*-1);i++)
                {
                    insert_random();
                }
        }

        void insert_random()
        {
            int tam = available_cells->size();
            int idx = rand() %tam;
            cell *auxCell;
            auxCell = available_cells->at(idx);
            int x = auxCell->x;
            int y = auxCell->y;
                field[y][x] = OBSTACLE;
                unavailable_cells->insert(unavailable_cells->begin(), auxCell);
                available_cells->erase(available_cells->begin()+idx);



        }

        void remove_random()
        {
            int tam = unavailable_cells->size();
            int idx = rand() %tam;
            cell *auxCell;
            auxCell = unavailable_cells->at(idx);
            int x = auxCell->x;
            int y = auxCell->y;
            field[y][x] = EMPTY;
            available_cells->insert(available_cells->begin(), auxCell);
            unavailable_cells->erase(unavailable_cells->begin()+idx);
        }

        bool move_kibus_to(int to,bool reflejo = false)
        {
            bool ret = false;
            if(kibus_exist)
            {
                switch(to)
                {
                case VIRTUAL_UP:
                    ret = set_kibus(kibus_cell->x,kibus_cell->y-1);
                    break;
                case VIRTUAL_DOWN:
                    ret = set_kibus(kibus_cell->x,kibus_cell->y+1);
                    break;
                case VIRTUAL_LEFT:
                    ret = set_kibus(kibus_cell->x-1,kibus_cell->y);
                    break;
                case VIRTUAL_RIGHT:
                    ret = set_kibus(kibus_cell->x+1,kibus_cell->y);
                    break;
                }
                if(ret && !reflejo)
                {
                    moves->insert(moves->begin(),to);
                }

            }

        }

        int regresa_uno()
        {
            int aux = moves->at(0);
            moves->erase(moves->begin());
            return refleja_movimiento(aux);
        }

        int refleja_movimiento(int i)
        {
            switch(i)
                {
                case VIRTUAL_UP:
                    return VIRTUAL_DOWN;
                    break;
                case VIRTUAL_DOWN:
                    return VIRTUAL_UP;
                    break;
                case VIRTUAL_LEFT:
                    return VIRTUAL_RIGHT;
                    break;
                case VIRTUAL_RIGHT:
                    return VIRTUAL_LEFT;
                    break;
                }
        }
        bool set_casa(int x,int y)
        {
            if(field[y][x] == EMPTY)
            {
                field[y][x] = CASA|KIBUS;
                casa_cell = new cell(x,y);
            kibus_exist = true;
            kibus_cell->x = x;
            kibus_cell->y = y;
                return true;
            }
            return false;

        }

        bool set_kibus(int x, int y)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (field[y][x] != EMPTY)
                return false;
            remove_kibus_from_map();
            kibus_exist = true;
            kibus_cell->x = x;
            kibus_cell->y = y;
            field[y][x] = KIBUS;
            return true;
        }
        void remove_casa()
        {
            if(casa_cell)
            {
                field[casa_cell->y][casa_cell->x] = EMPTY;
                free(casa_cell);
                casa_cell = NULL;
            }
        }

        void remove_kibus_from_map()
        {
            if (kibus_cell->x>=0)
            {
                field[kibus_cell->y][kibus_cell->x] = field[kibus_cell->y][kibus_cell->x]&CASA;
                kibus_exist = false;
            }
        }

        void init_field()
        {
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    field[i][j] = EMPTY;
                    available_cells->insert(available_cells->end(),new cell(j,i));
                }
            }
            cout<<"available vector size "<<available_cells->size()<<endl;
        }

        void to_string()
        {
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    cout<<field[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        void print_cell_vector()
        {
            for (unsigned int i = 0;i<available_cells->size();i++)
            {
                cout<<available_cells->at(i)->x<<" "<<available_cells->at(i)->y<<endl;
            }
        }
        int number_of_items(int p)
        {
            return (Y_MAX*X_MAX*p/100);
        }
        virtual ~virtual_field() {}
    protected:
    private:
};

#endif // VIRTUAL_FIELD_H
