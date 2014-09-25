#ifndef PIEDRA_H_INCLUDED
#define PIEDRA_H_INCLUDED
class Piedra
{
public:
    Glib::RefPtr<Gdk::Pixbuf> piedra_sprite;
    Piedra()
    {
        piedra_sprite = Gdk::Pixbuf::create_from_file("images/piedra.png");
    }
    void drawing_in_background(Glib::RefPtr<Gdk::Pixbuf> ground,int x,int y)
    {
        int posx = x*32;
        int posy = y*32;
        piedra_sprite->composite(ground,posx,posy,piedra_sprite->get_width(),piedra_sprite->get_height(),posx,posy,1,1,Gdk::INTERP_NEAREST,255);
    }
};


#endif // PIEDRA_H_INCLUDED
