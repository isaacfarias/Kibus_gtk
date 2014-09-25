#ifndef CASA_H_INCLUDED
#define CASA_H_INCLUDED

class Casa
{
public:
    Glib::RefPtr<Gdk::Pixbuf> casa_sprite;
    Casa()
    {
        casa_sprite = Gdk::Pixbuf::create_from_file("images/casa.png");
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y)
    {
        int posx = x*32;
        int posy = y*32;
        casa_sprite->composite(ground,posx,posy,casa_sprite->get_width(),casa_sprite->get_height(),posx,posy,1,1,Gdk::INTERP_NEAREST,255);
    }
};



#endif // CASA_H_INCLUDED
