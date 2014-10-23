#ifndef PASTO_H_INCLUDED
#define PASTO_H_INCLUDED
class Pasto
{
public:
    Glib::RefPtr<Gdk::Pixbuf> pasto_sprite;
    Pasto(char src[])
    {
        pasto_sprite = Gdk::Pixbuf::create_from_file(src);
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y)
    {
        int posx = x*32;
        int posy = y*32;
        pasto_sprite->composite(ground,posx,posy,pasto_sprite->get_width(),pasto_sprite->get_height(),posx,posy,1,1,Gdk::INTERP_NEAREST,255);
    }
};


#endif // PASTO_H_INCLUDED
