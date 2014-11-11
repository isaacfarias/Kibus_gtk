#ifndef ABEJA_H_INCLUDED
#define ABEJA_H_INCLUDED

class Abeja
{
public:
    Glib::RefPtr<Gdk::Pixbuf> abeja_sprite;
    Abeja(char src[])
    {
        abeja_sprite = Gdk::Pixbuf::create_from_file(src);
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y)
    {
        int posx = x*32;
        int posy = y*32;
        //debug
        int spriteW = abeja_sprite->get_width();
        int groundW = ground->get_width();

        abeja_sprite->composite(ground,posx,posy,abeja_sprite->get_width(),abeja_sprite->get_height(),posx,posy,1,1,Gdk::INTERP_NEAREST,255);
    }
};



#endif // ABEJA_H_INCLUDED
