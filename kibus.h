#ifndef KIBUS_H_INCLUDED
#define KIBUS_H_INCLUDED

#include <gtkmm.h>
#include <iostream>
using namespace std;
using namespace Gtk;

#define KIBUS_UP 0
#define KIBUS_DOWN 1
#define KIBUS_LEFT 2
#define KIBUS_RIGHT 3
class Kibus
{
    Glib::RefPtr<Gdk::Pixbuf> kibus_sprites;
    //Glib::RefPtr<Gdk::Pixbuf> return_background;
    Glib::RefPtr<Gdk::Pixbuf> actual_sprite;
    int number_actual_sprite;
    public:
    int posX,posY,virtual_posX,virtual_posY;


    Kibus()
    {
        kibus_sprites = Gdk::Pixbuf::create_from_file("images/kibus_sprites.png"); //        kibus_sprites = Gdk::Pixbuf::create_from_file("images/kibus_sprites.png");
        actual_sprite = Gdk::Pixbuf::create_subpixbuf(kibus_sprites,64,0,32,32);
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y)
    {
        int aux_x = x*32;
        int aux_y = y*32;
        actual_sprite->composite(ground,aux_x,aux_y,actual_sprite->get_width(),actual_sprite->get_height(),aux_x,aux_y,1,1,Gdk::INTERP_NEAREST,255);

        /*
        def copy_area_composite(source_buf, source_x, source_y, width, height, dest_buf, dest_x, dest_y):
        source_buf.composite(dest_buf, dest_x, dest_y, width, height, dest_x-src_x, dest_y-rect_y, 1, 1, GdkPixbuf.InterpType.NEAREST, 255)
        */
    }
    void move_to(int direction)
    {
        switch(direction)
        {
        case KIBUS_UP:
            actual_sprite = Gdk::Pixbuf::create_subpixbuf(kibus_sprites,0,0,32,32);
            break;
        case KIBUS_DOWN:
            actual_sprite = Gdk::Pixbuf::create_subpixbuf(kibus_sprites,64,0,32,32);
            break;
        case KIBUS_LEFT:
            actual_sprite = Gdk::Pixbuf::create_subpixbuf(kibus_sprites,32*5,0,32,32);
            break;
        case KIBUS_RIGHT:
            actual_sprite = Gdk::Pixbuf::create_subpixbuf(kibus_sprites,32*6,0,32,32);
            break;
        }

    }
    int get_posX()
    {
        return virtual_posX*32;
    }
    int get_posY()
    {
        return virtual_posY*32;
    }
};

#endif // KIBUS_H_INCLUDED
