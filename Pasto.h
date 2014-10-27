#ifndef PASTO_H_INCLUDED
#define PASTO_H_INCLUDED
class Pasto
{
public:
    Glib::RefPtr<Gdk::Pixbuf> pasto_sprite;
    Glib::RefPtr<Gdk::Pixbuf> pasto_sprite_s;
    Pasto(char src[])
    {
        pasto_sprite = Gdk::Pixbuf::create_from_file(src);
        pasto_sprite_s = pasto_sprite->copy();
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y,float sat = 1.0)
    {

        pasto_sprite_s = pasto_sprite->copy();
        pasto_sprite_s->saturate_and_pixelate(pasto_sprite_s,sat,false);
        int posx = x*32;
        int posy = y*32;
        pasto_sprite_s->composite(ground,posx,posy,pasto_sprite->get_width(),pasto_sprite->get_height(),posx,posy,1,1,Gdk::INTERP_NEAREST,255);
    }
};


#endif // PASTO_H_INCLUDED
