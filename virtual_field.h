#ifndef VIRTUAL_FIELD_H
#define VIRTUAL_FIELD_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "utilities.h"
#include "cell.h"

using std::cout;
using std::endl;

#define X_MAX 20
#define Y_MAX 15

const float STEP_TEMP  = 3.0/(X_MAX-1);



#define KIBUS        0b0001
#define OBSTACLE     0b0010
#define CASA         0b0100
#define WALKABLE     0b1000
#define ABEJA       0b10000
#define W_1           ((1<<5)|WALKABLE)
#define W_2           ((2<<5)|WALKABLE)
#define W_3           ((3<<5)|WALKABLE)
#define VIRTUAL_UP 0
#define VIRTUAL_DOWN 1
#define VIRTUAL_LEFT 2
#define VIRTUAL_RIGHT 3
#define NUM_ABEJAS 5
class virtual_field
{
    public:
        int field[Y_MAX][X_MAX];
        cell *kibus_cell;
        cell *casa_cell;
        cell *ultima_pos;
        std::vector <cell> *abejas;
        bool kibus_exist;
        bool is_at_home;
        std::vector <cell*> *available_cells;
        std::vector <cell*> *unavailable_cells;
        std::vector <cell> *vecinos_de_kibus_1;
        std::vector <cell> *vecinos_de_abejas;
        std::vector <cell> *path;
        std::vector <cell*> *vecinos_de_kibus_3;
        std::vector <int> *moves;

        virtual_field()
        {
            kibus_cell = new cell(-1,-1);
            ultima_pos = new cell(-1,-1);
            is_at_home = false;
            casa_cell = NULL;
            kibus_exist = false;
            available_cells = new std::vector<cell*>();
            unavailable_cells = new std::vector<cell*>();
            vecinos_de_kibus_1 = new std::vector<cell>();
            vecinos_de_abejas = new std::vector<cell>();
            path = new std::vector<cell>();
            init_field();
            moves = new std::vector<int>();
            abejas = new std::vector<cell>();
            //print_cell_vector();
            //to_string();
            //number_of_items(20);
            //for(int i=0;i<NUM_ABEJAS;i++)
            //{
            /*
            for (int i = 0 ;i < NUM_ABEJAS; i++)
            {
                abejas->insert(abejas->begin(),*(new cell(-1,-1)));
                field[i][i]=set_mask(field[i][i],ABEJA);
            }
*/
            //}
        }
        void set_virtual_abeja(cell c)
        {
            field[c.y][c.x]=set_mask(field[c.y][c.x],ABEJA);
        }

        bool esta_en_path(cell c)
        {
            int TAM = path->size();
            for (int i=0;i<TAM;i++)
            {
                if (c == path->at(i))
                {
                    return true;
                }
            }
            return false;
        }


        void mover_abejas()
        {
            cout<<"virtual_field::mover_abejas"<<endl;
            cell aux = abejas->at(0);
            if (esta_en_path(aux))
            {
                enfriar_celda(aux);
            }
            if (!is_at_home)
                {
                    path->insert(path->end(),aux);
                    liberar_abejas_en_mapa_virtual(aux);
                    is_at_home = esta_en_casa(aux);

           }// print_cell_vector(path);
        }


        void move_kibus_temperature()
        {
            /*Linerar abejas
            quitar_abejas_en_mapa_virtual();
            liberar_abejas_en_mapa_virtual(*kibus_cell);*/

        }
        void liberar_abejas_en_mapa_virtual(cell c)
        {
            quitar_abejas_en_mapa_virtual();
            abejas->clear();
            generar_vecinos(&c,vecinos_de_abejas);
            int tam = vecinos_de_abejas->size();
            if (tam > NUM_ABEJAS)
                tam = NUM_ABEJAS;
            for (int i = 0;i<tam;i++)
            {
                set_virtual_abeja(vecinos_de_abejas->at(i));
                abejas->insert(abejas->begin(),vecinos_de_abejas->at(i));
            }
            std::sort(abejas->begin(),abejas->end());
        }

        void quitar_abejas_en_mapa_virtual()
        {
            int tam = abejas->size();
            for (int i = 0;i<tam;i++)
            {
                remove_abeja_from_map(abejas->at(i));
            }
        }

        void generar_vecinos(cell *c,std::vector <cell> *v)
        {
            v->clear();
            for (int x = -1;x<=1;x++)
            {
                for(int y = -1; y <= 1; y++)
                {
                    int new_x = c->x+x,new_y = c->y+y;
                    if (((new_x < 0) || (new_x >= X_MAX)) || ((new_y < 0 )|| (new_y >= Y_MAX)) || (x==0&&y==0) )
                        continue;
                    else
                    {
                        /*TODO change for a switch for diferent lists*/

                        if(es_(field[new_y][new_x],WALKABLE))
                        {
                            cell aux = cell(new_x,new_y,field[new_y][new_x]);
                            if(!(aux == (*ultima_pos))) /*TODO Check if works with last position*/
                            v->insert(v->begin(),aux);

                        }

                    }
                }
            }
            if(v->size()==0)
                v->insert(v->begin(),(*ultima_pos));
            std::random_shuffle(v->begin(),v->end());

        }

        cell toma_vecino_random(std::vector <cell> *v)
        {
            int tam = v->size();
            int idx;
            if(tam)
            {
                idx = rand() %tam;
                return v->at(0);
            }
        }

        /*TODO Adapt to temperature logic*/
        bool esta_en_casa(cell c)
        {
            if ((c.v>>6) == 1)
            {
                return true;
            }
            /*
            cell aux = bresenham_next_cell((*kibus_cell),(*casa_cell));
            bool ret = (*casa_cell) == aux;*/
            //free(aux);
            return false;
        }

        bool esta_en_casa()
        {
            if ((kibus_cell->v>>6) == 1)
            {
                return true;
            }
            /*
            cell aux = bresenham_next_cell((*kibus_cell),(*casa_cell));
            bool ret = (*casa_cell) == aux;*/
            //free(aux);
            return false;
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
            field[y][x] = WALKABLE;
            available_cells->insert(available_cells->begin(), auxCell);
            unavailable_cells->erase(unavailable_cells->begin()+idx);
        }

        bool set_casa(int x,int y)
        {
            if(es_(field[y][x],WALKABLE))
            {
                remove_casa();
                field[y][x] = CASA;
                casa_cell = new cell(x,y);
                calculate_field_temperature();
                return true;
            }
            return false;

        }

        void calculate_field_temperature()
        {
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    if(es_(field[i][j], WALKABLE))
                    {
                        field[i][j] = WALKABLE|(calculate_cell_temperature(*casa_cell,j,i)<<6);
                    }
                }
            }
        }

        int calculate_cell_temperature(cell casa, int x, int y)
        {
            int d_x = ABS((casa.x-x));
            int d_y = ABS(casa.y-y);
            if(d_x>d_y)
                return d_x;
            else
                return d_y;
        }

        float get_normalized_temp(int val)
        {
            return -1*(val * STEP_TEMP -1)+2;
        }

        bool set_kibus(int x, int y,bool bees = false)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (!es_(field[y][x], WALKABLE))
                return false;
            remove_kibus_from_map();
            kibus_exist = true;

            cell c(x,y);
            if((*ultima_pos) == c)
            {
                enfriar_celda(c); /*TODO checkit */
            }
            ultima_pos->x = kibus_cell->x;
            ultima_pos->y = kibus_cell->y;
            kibus_cell->x = x;
            kibus_cell->y = y;
            field[y][x] = field[y][x]|KIBUS;
            //to_string();
            generar_vecinos(kibus_cell,vecinos_de_kibus_1);
            if (bees)
            {
                is_at_home = false;
                liberar_abejas_en_mapa_virtual(*kibus_cell);
            }

            return true;
        }

        bool set_obstaculo(int x,int y)
        {
            if((x<0 || x>=X_MAX) || (y<0 || y>=Y_MAX))
                return false;
            if (!es_(field[y][x],WALKABLE))
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
                field[y][x] = WALKABLE;
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
                field[casa_cell->y][casa_cell->x] = WALKABLE;
                free(casa_cell);
                casa_cell = NULL;
            }
        }

        void remove_kibus_from_map()
        {
            if (kibus_cell->x>=0)
            {
                int v = field[kibus_cell->y][kibus_cell->x];
                int d = field[kibus_cell->y][kibus_cell->x]=field[kibus_cell->y][kibus_cell->x]&0b111111111111111111111110;// = field[kibus_cell->y][kibus_cell->x]&CASA;
                kibus_exist = false;
            }
        }

        void remove_abeja_from_map(cell c)
        {
            if (c.x>=0)
            {
                //enfriar_celda(c);
                int d = field[c.y][c.x]=field[c.y][c.x]&0b11111111111111111111101111;
            }
        }

        void enfriar_celda(cell c)
        {
            int val = (field[c.y][c.x]>>6)+1;
            field[c.y][c.x] =((val<<6)|WALKABLE);
        }

        void init_field()
        {
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    field[i][j] = WALKABLE;
                    available_cells->insert(available_cells->end(),new cell(j,i));
                }
            }
        }

        void to_string_temp()
        {
            cout.precision(1);
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    cout<<(get_normalized_temp(field[i][j]>>5))<<setw(4);
                }
                cout<<endl;
            }
            cout<<endl;
        }

        void to_string()
        {
            for(int i = 0;i<Y_MAX;i++)
            {
                for(int j = 0 ;j<X_MAX;j++)
                {
                    cout<<field[i][j]<<setw(4);
                }
                cout<<endl;
            }
            cout<<endl;
        }
        void print_cell_vector(std::vector <cell> *v)
        {
            for (unsigned int i = 0;i<v->size();i++)
            {
                cout<<v->at(i).x<<" "<<v->at(i).y<<", "<<v->at(i).v<<endl;
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

        void save_field(char fileName[])
        {
            ofstream out_file(fileName);
            for (int i = 0;i<Y_MAX;i++)
            {
                for (int j=0;j<X_MAX;j++)
                {
                    out_file<<field[i][j]<<" ";
                }
                out_file<<endl;
            }
            out_file.close();
        }

        void load_field(char fileName[])
        {
            ifstream in_file(fileName);
            init_field();
            for (int i = 0;i<Y_MAX;i++)
            {
                for (int j=0;j<X_MAX;j++)
                {
                    int v;

                    in_file>>v;
                    if(es_(v,OBSTACLE))
                    {

                        set_obstaculo(j,i);
                    }
                    else
                        field[i][j] = v;
                }
            }
            in_file.close();
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
        /*
        bool move_kibus_bresenham()
        {
            if(esta_en_casa())
                return false;
            cell aux = bresenham_next_cell((*kibus_cell),(*casa_cell));
            if((field[aux.y][aux.x]>24)||!set_kibus(aux.x,aux.y))
            {
                int aux_value = (field[kibus_cell->y][kibus_cell->x]>>4)+1;
                int deb1 = (aux_value<<4);
                int deb2 =(field[kibus_cell->y][kibus_cell->x]&0b1111);
                int deb3 = field[kibus_cell->y][kibus_cell->x] = (field[kibus_cell->y][kibus_cell->x]&0b1111)|deb1;
                //free(aux);
                generar_vecinos();
                aux = toma_vecino_random();
                    set_kibus(aux.x,aux.y);
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
        */

        virtual ~virtual_field() {}
    protected:
    private:
};



#endif // VIRTUAL_FIELD_H
