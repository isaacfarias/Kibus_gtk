#include <gtkmm.h>
#include <iostream>
#include "Field.h"
#include <unistd.h>

using namespace std;
using namespace Gtk;
class Main_window
{
    public:

    Gtk::Window *GTK_window;
    Gtk::Button *button_up,*button_down,*button_left,*button_right;
    Gtk::Button *button_return;
    Gtk::Scale *scale_obstacles;
    Glib::RefPtr<Gtk::Adjustment> adjustment_obstacles;
    Gtk::ToggleButton *togglebutton_home;
    Gtk::ToggleButton *togglebutton_kibus;
    Gtk::ToggleButton *togglebutton_obstaculo;
    Gtk::ToggleButton *togglebutton_q_obstaculo;

    Gtk::DrawingArea * drawingarea_field;
    Field *field;
    Gtk::Label * label_debug;
    Glib::RefPtr<Gtk::Builder> builder;
    Glib::RefPtr<Gtk::Application> app;
    Glib::Dispatcher *m_dispacher;
    Glib::Threads::Thread *m_thread;


        Main_window(Glib::RefPtr<Gtk::Application> application)
        {
            builder = Gtk::Builder::create_from_file("interface_layout/interface.glade");
            cout<<builder<<" GTK_builder from 'interface_layout/interface.glade'" <<endl;
            builder->get_widget("window_main",GTK_window);
            cout<<GTK_window<<" GTK_window creation"<<endl;
            //GTK_window->signal_key_press_event().connect(sigc::mem_fun(*this,&Main_window::key_pressed_callback));
            //setup_pad();
            setup_panel();
            setup_drawingarea_field();
            builder->get_widget("label_debug",label_debug);
            app = application;
            m_dispacher = new Glib::Dispatcher();
            m_dispacher->connect(sigc::mem_fun(*this,&Main_window::update_draw));



        }

        bool key_pressed_callback(GdkEventKey *e)
        {
            cout<<"Key val"<< e->keyval <<"Hardware"<<e->hardware_keycode<<endl;
            switch(e->hardware_keycode)
            {
            case 25:
                button_up->clicked();
                break;
            case 38:
                button_left->clicked();
                break;

            case 39:
                button_down->clicked();
                break;
            case 40:
                button_right->clicked();
                break;
            }
            return true;
        }

        void update_draw()
        {
            field->drawing_area->queue_draw();
            //usleep(1000000);
        }

        void setup_drawingarea_field()
        {
            builder->get_widget("drawingarea_field",drawingarea_field);
            field = new Field(drawingarea_field);
        }

        void setup_panel()
        {
            builder->get_widget("button_return",button_return);
            button_return->signal_clicked().connect(sigc::mem_fun(*this,&Main_window::button_return_callback));
            builder->get_widget("scale_obstacles",scale_obstacles);
            adjustment_obstacles = scale_obstacles->get_adjustment();
            adjustment_obstacles->signal_value_changed().connect(sigc::mem_fun(*this,&Main_window::scale_obstacles_callback));
            builder->get_widget("togglebutton_home",togglebutton_home);
            togglebutton_home->signal_toggled().connect(sigc::mem_fun(*this,&Main_window::togglebutton_home_callback));
            builder->get_widget("togglebutton_obstaculo",togglebutton_obstaculo);
            togglebutton_obstaculo->signal_toggled().connect(sigc::mem_fun(*this,&Main_window::togglebutton_obstaculo_callback));
            builder->get_widget("togglebutton_kibus",togglebutton_kibus);
            togglebutton_kibus->signal_toggled().connect(sigc::mem_fun(*this,&Main_window::togglebutton_kibus_callback));
            builder->get_widget("togglebutton_q_obstaculo",togglebutton_q_obstaculo);
            togglebutton_q_obstaculo->signal_toggled().connect(sigc::mem_fun(*this,&Main_window::togglebutton_q_obstaculo_callback));
        }



        void button_return_callback()
        {
            cout<<"button_return_callback"<<endl;

            if (!field->v->esta_en_casa())
            {

                field->move_kibus_bresenham();
                m_thread = Glib::Threads::Thread::create(sigc::bind(sigc::mem_fun(this, &Main_window::timer_to_move), this));

            }

        }

        void timer_to_move(Main_window *caller)
        {

            usleep(100000);
            button_return->clicked();

        }

        void scale_obstacles_callback()
        {
            cout<<"scale_obstacles_callback "<<adjustment_obstacles->get_value()<<endl;
            int values = adjustment_obstacles->get_value();
            field->v->set_random(values);
            field->drawing_area->queue_draw();
        }

        void togglebutton_home_callback()
        {
            cout<<"togglebutton_home_callback "<<togglebutton_home->get_active()<<endl;


            if(!togglebutton_home->get_active())
            {
                //field->v->remove_kibus_from_map();
                //field->v->remove_casa();
                //field->v->moves->erase(field->v->moves->begin(),field->v->moves->end());
                scale_obstacles->set_sensitive(true);
            }
            else
            {
                scale_obstacles->set_sensitive(false);
                set_toogle_on_virtual_field(TOOGLE_CASA);
            }
        }

        void togglebutton_kibus_callback()
        {
            cout<<"togglebutton_kibus_callback "<<togglebutton_kibus->get_active()<<endl;


            if(!togglebutton_kibus->get_active())
            {
                //field->v->remove_kibus_from_map();
                //field->v->remove_casa();
                //field->v->moves->erase(field->v->moves->begin(),field->v->moves->end());
                scale_obstacles->set_sensitive(true);
            }
            else
            {
                scale_obstacles->set_sensitive(false);
                set_toogle_on_virtual_field(TOOGLE_KIBUS);
            }
        }

        void togglebutton_obstaculo_callback()
        {
            cout<<"togglebutton_obstaculo_callback "<<togglebutton_obstaculo->get_active()<<endl;


            if(!togglebutton_obstaculo->get_active())
            {
                //field->v->remove_kibus_from_map();
                //field->v->remove_casa();
                //field->v->moves->erase(field->v->moves->begin(),field->v->moves->end());
                scale_obstacles->set_sensitive(true);
            }
            else
            {
                scale_obstacles->set_sensitive(false);
                set_toogle_on_virtual_field(TOOGLE_OBSTACULO);
            }
        }

        void togglebutton_q_obstaculo_callback()
        {
            cout<<"togglebutton_q_obstaculo_callback "<<togglebutton_q_obstaculo->get_active()<<endl;


            if(!togglebutton_q_obstaculo->get_active())
            {
                //field->v->remove_kibus_from_map();
                //field->v->remove_casa();
                //field->v->moves->erase(field->v->moves->begin(),field->v->moves->end());
                scale_obstacles->set_sensitive(true);
            }
            else
            {
                scale_obstacles->set_sensitive(false);
                set_toogle_on_virtual_field(TOOGLE_Q_OBSTACULO);
            }
        }

        void set_toogle_on_virtual_field(int t)
        {
            field->set_toogle(t);
            switch(t)
            {
            case TOOGLE_CASA:
                togglebutton_kibus->set_active(false);
                togglebutton_obstaculo->set_active(false);
                togglebutton_q_obstaculo->set_active(false);
                break;
            case TOOGLE_KIBUS:
                togglebutton_home->set_active(false);
                togglebutton_obstaculo->set_active(false);
                togglebutton_q_obstaculo->set_active(false);
                break;
            case TOOGLE_OBSTACULO:
                togglebutton_home->set_active(false);
                togglebutton_kibus->set_active(false);
                togglebutton_q_obstaculo->set_active(false);
                break;
                case TOOGLE_Q_OBSTACULO:
                togglebutton_home->set_active(false);
                togglebutton_kibus->set_active(false);
                togglebutton_obstaculo->set_active(false);
                break;
            }
        }

        void setup_pad()
        {
            builder->get_widget("button_up",button_up);
            button_up->signal_clicked().connect(sigc::mem_fun(*this,&Main_window::pad_up));

            builder->get_widget("button_down",button_down);
            button_down->signal_clicked().connect(sigc::mem_fun(*this,&Main_window::pad_down));

            builder->get_widget("button_left",button_left);
            button_left->signal_clicked().connect(sigc::mem_fun(*this,&Main_window::pad_left));

            builder->get_widget("button_right",button_right);
            button_right->signal_clicked().connect(sigc::mem_fun(*this,&Main_window::pad_right));
        }

        void pad_right()
        {
            field->move_kibus(KIBUS_RIGHT);
        }

        void pad_left()
        {
            field->move_kibus(KIBUS_LEFT);
        }

        void pad_up()
        {
            field->move_kibus(KIBUS_UP);
        }

        void pad_down()
        {
            field->move_kibus(KIBUS_DOWN);
        }
        int run()
        {
            return app->run(*GTK_window);
        }


};
