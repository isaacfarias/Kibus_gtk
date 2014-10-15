#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
//#define showMotionEvents
#include <gtkmm.h>
#include <iostream>
#include "kibus.h"
#include "piedra.h"
#include "casa.h"
#include "virtual_field.h"
#define size_x 20
#define size_y 15
#define TOOGLE_CASA 1
#define TOOGLE_KIBUS 2
#define TOOGLE_OBSTACULO 3
#define TOOGLE_Q_OBSTACULO 4
using namespace std;
using namespace Gtk;
class Field
{
public:
    DrawingArea *drawing_area;
    Glib::RefPtr<Gdk::Pixbuf> background;
    Glib::RefPtr<Gdk::Pixbuf> background_with_draws;
    Cairo::RefPtr<Cairo::Context> cairo_context;
    Piedra *piedra;
    Casa *casa;
    Kibus *kibus;
    int toogle_selected;
    virtual_field *v;

    Field(DrawingArea *d)
    {
        drawing_area = d;
        //drawing_area->add_events(Gdk::POINTER_MOTION_MASK);
        drawing_area->add_events(Gdk::BUTTON_PRESS_MASK);
        //drawing_area->signal_motion_notify_event().connect(sigc::mem_fun(*this,&Field::signal_motion_notify_event_callback));
        drawing_area->signal_button_press_event().connect(sigc::mem_fun(*this,&Field::signal_button_press_event_callback));
        background = Gdk::Pixbuf::create_from_file("images/background.png");
        background_with_draws = background->copy();
        drawing_area->signal_draw().connect(sigc::mem_fun(*this,&Field::signal_draw_callback));
        v=new virtual_field();
        kibus = new Kibus();
        piedra = new Piedra();
        casa = new Casa();
        toogle_selected = 0;
    }

    bool signal_draw_callback(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        cairo_context = cr;
        cout<<"signal_draw_callback"<<endl;
        //kibus->drawing_in_background(background);
        background_with_draws = background->copy();
        for (int y = 0;y<size_y;y++)
        {
            for (int x = 0 ; x<size_x;x++)
            {
                int aux = v->field[y][x];

                if (aux&OBSTACLE)
                        piedra->drawing_in_background(background_with_draws,x,y);
                if (aux & CASA)
                        casa->drawing_in_background(background_with_draws,x,y);
                if (aux&KIBUS)
                        kibus->drawing_in_background(background_with_draws,x,y);
            }
        }
        Gdk::Cairo::set_source_pixbuf(cr,background_with_draws);
        cr->rectangle(0,0,background_with_draws->get_width(),background_with_draws->get_height());

        cr->fill();
        return true;
    }

    void move_kibus(int direction,bool reflejo = false)
    {
        switch(direction)
        {
        case KIBUS_UP:
            v->move_kibus_to(VIRTUAL_UP,reflejo);
            break;
        case KIBUS_DOWN:
            v->move_kibus_to(VIRTUAL_DOWN,reflejo);
            break;
        case KIBUS_LEFT:
            v->move_kibus_to(VIRTUAL_LEFT,reflejo);
            break;
        case KIBUS_RIGHT:
            v->move_kibus_to(VIRTUAL_RIGHT,reflejo);
            break;
        }
        kibus->move_to(direction);
        drawing_area->queue_draw();

    }
    void move_kibus_bresenham()
    {

        v->move_kibus_bresenham();
        drawing_area->queue_draw();

    }



    bool signal_button_press_event_callback(GdkEventButton *e)
    {
        if((e->button==1))
        {
            int x_v = e->x/32;
            int y_v = e->y/32;
            cout<<"X: "<< x_v; cout<<", Y: "<<y_v<<endl;
            switch (toogle_selected)
            {
                    case TOOGLE_CASA:
                        v->set_casa(x_v,y_v);
                    break;
                    case TOOGLE_KIBUS:
                        v->set_kibus(x_v,y_v);
                        break;
                    case TOOGLE_OBSTACULO:
                        v->set_obstaculo(x_v,y_v);
                        break;
                    case TOOGLE_Q_OBSTACULO:
                        v->remove_obstaculo(x_v,y_v);
                        break;
                    default:
                        break;


            }
                drawing_area->queue_draw();
        }
        cout<<endl;
        return true;
    }

    bool signal_motion_notify_event_callback(GdkEventMotion *e)
    {
        #ifdef showMotionEvents
        cout<<"signal_motion_notify_event_callback X: "<< e->x ;
        cout<<", Y: "<<e->y<<endl;
        #endif // showMotionEvents
        return true;
    }
    void set_toogle(int t)
    {
        toogle_selected = t;

    }
} ;


#endif // FIELD_H_INCLUDED
