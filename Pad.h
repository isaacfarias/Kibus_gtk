#include <gtkmm.h>
#include <iostream>
using namespace std;

class Pad
{
    public:
        Gtk::Button *button_up,*button_down,*button_left,*button_right;
        Pad(Glib::RefPtr<Gtk::Builder> builder)
        {
            builder->get_widget("button_up",button_up);
            builder->get_widget("button_down",button_down);
            builder->get_widget("button_left",button_left);
            builder->get_widget("button_right",button_right);
        }

};
