
#include <gtkmm.h>
#include "Window.h"
int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Main_window main_window(app);
    /*
    Gtk::Window window;
    window.set_default_size(200, 200);
    */

  return main_window.run(); //app->run(window);
}
