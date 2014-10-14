#ifndef VIRTUAL_FIELD_H
#define VIRTUAL_FIELD_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "utilities.h"
#include "cell.h"
using std::cout;
using std::endl;

#define X_MAX 20
#define Y_MAX 15

#define EMPTY        0b1000
#define KIBUS        0b0001
#define OBSTACLE     0b0010
#define CASA         0b0100
#define WALKABLE     0b1000
#define W_1           ((1<<4)|WALKABLE)
#define W_2           ((2<<4)|WALKABLE)
#define W_3           ((3<<4)|WALKABLE)
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
        std::vector <cell*> *vecinos_de_kibus;
        std::vector <int> *moves;

        virtual_field()
        {
            kibus_cell = new cell(-1,-1);
            home_alone = false;
            casa_cell = NULL;
            kibus_exist = false;
            available_cells = new std::vector<cell*>();
            unavailable_cells = new std::vector<cell*>();
            vecinos_de_kibus = new std::vector<cell*>();
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

        void generar_vecinos()
        {
            cell* aux;
            vecinos_de_kibus->clear();
            for (int x = -1;x<=1;x++)
            {
                for(int y = -1; y <= 1; y++)
                {
                    if (((kibus_cell->x+x < 0) || (kibus_cell->x+x >= X_MAX)) || ((kibus_cell->y+y < 0 )|| (kibus_cell->y+y >= Y_MAX)) || (x==0&&y==0) )
                        continue;
                    else
                    {
                        if(field[kibus_cell->y+y][kibus_cell->x+x] == EMPTY)
                        {


                        aux = new cell(kibus_cell->x+x,kibus_cell->y+y);
                        aux->to_string();
                        vecinos_de_kibus->insert(vecinos_de_kibus->begin(),aux);
                        }
                    }
                }
            }

        }

        cell* toma_vecino_random()
        {
            int tam = vecinos_de_kibus->size();
            if(!tam)
                return NULL;
            int idx = rand() %tam;
            return vecinos_de_kibus->at(idx);
        }


        bool esta_en_casa()
        {
            cell *aux = bresenham_next_cell((*kibus_cell),(*casa_cell));
            bool ret = (*casa_cell) == (*aux);
            free(aux);
            return ret;
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

        bool move_kibus_bresenham()
        {
            if(esta_en_casa())
                return false;
            cell *aux = bresenham_next_cell((*kibus_cell),(*casa_cell));
            if(!set_kibus(aux->x,aux->y))
            {
                free(aux);
                aux = toma_vecino_random();
                if (aux)
                    set_kibus(aux->x,aux->y);
            }


        }

        bool move_kibus_to(int to,bool reflejo = false)
        {
            if(kibus_exist)
            {
                switch(to)
                {
                case VIRTUAL_UP:
                    return set_kibus(kibus_cell->x,kibus_cell->y-1);
                    break;
                case VIRTUAL_DOWN:
                    return set_kibus(kibus_cell->x,kibus_cell->y+1);
                    break;
                case VIRTUAL_LEFT:
                    return set_kibus(kibus_cell->x-1,kibus_cell->y);
                    break;
                case VIRTUAL_RIGHT:
                    return set_kibus(kibus_cell->x+1,kibus_cell->y);
                    break;
                }
            }

        }

        bool set_casa(int x,int y)
        {
            if(field[y][x] == EMPTY)
            {
                remove_casa();
                field[y][x] = CASA;
                casa_cell = new cell(x,y);
                /*
            kibus_exist = true;
            kibus_cell->x = x;
            kibus_cell->y = y;*/
                return true;
            }
            return false;

        }

        bool set_kibus(int x, int y)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (!es_(field[y][x], WALKABLE))
                return false;
            remove_kibus_from_map();
            kibus_exist = true;
            kibus_cell->x = x;
            kibus_cell->y = y;
            field[y][x] = KIBUS;
            generar_vecinos();
            return true;
        }

        bool set_obstaculo(int x,int y)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (field[y][x] != EMPTY)
                return false;
            cell c(x,y);
            int idx = buscar_elemento(available_cells,c);
            if(idx >=0 )
            {
                unavailable_cells->insert(unavailable_cells->begin(), available_cells->at(idx));
                available_cells->erase(available_cells->begin()+idx);
                field[y][x] = OBSTACLE;
            }

        }

        bool remove_obstaculo(int x,int y)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (field[y][x] != OBSTACLE)
                return false;
            cell c(x,y);
            int idx = buscar_elemento(unavailable_cells,c);
            if(idx >=0 )
            {
                available_cells->insert(available_cells->begin(), unavailable_cells->at(idx));
                unavailable_cells->erase(unavailable_cells->begin()+idx);
                field[y][x] = EMPTY;
            }

        }

        void eliminar_elemento_vector(std::vector <cell*> *v, int idx)
        {

        }

        int buscar_elemento(std::vector <cell*> *v,cell &c)
        {
            for(int j = 0 ;j<v->size();j++)
                {
                    cell *aux = v->at(j);
                    if( (*aux)== c)
                        return j;
                }
                return -1;
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
                field[kibus_cell->y][kibus_cell->x]=set_mask(0,EMPTY);// = field[kibus_cell->y][kibus_cell->x]&CASA;
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
        bool es_(int valor_celda, int mask)
        {
            return ((valor_celda&mask)==mask);
        }
        int set_mask(int valor_celda,int mask)
        {
            return (valor_celda|mask);
        }
        virtual ~virtual_field() {}
    protected:
    private:
};



#endif // VIRTUAL_FIELD_H
