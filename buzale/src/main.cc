/*<HTML><listing><BODY>                 Time-stamp: <11 Jan 01 20:12:31 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  01.09.2000
#  Ersteller    :  Markus Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung :  Main-Modul für das Spiel CHAR
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";


#include <gtk--/main.h>
#include <gtk--/window.h>
#include <gtk--/table.h>
#include <gtk--/style.h>

#include <tasten.hh>
#include <bild.hh>
#include <menu.hh>
#include <logik.hh>
#include <count.hh>
#include <input.hh>
#include <fenster.hh>
#include <icon.xpm>

using SigC::slot;

class Window : public Gtk::Window
{
protected:
  Menu    m;
  Tasten  t;
  Fenster f;
  Logik   l;
  Gtk::Table table;
public:
  Window();
  gint delete_event_impl(GdkEventAny*) { Gtk::Main::instance()->quit(); return 0; }
  void realize_callback(void);
};

Window::Window() : Gtk::Window(), table(3,3), m(), t(), f(), l(m,t,f)
{  
  realize.connect(slot(this,&Window::realize_callback));
  m.show();
  f.show();
  table.attach(m                    ,0,3,0,1);
  table.attach(f                    ,1,2,2,3);
  table.attach(t.get_widget_oben()  ,1,3,1,2);
  table.attach(t.get_widget_rechts(),2,3,2,4);
  table.attach(t.get_widget_unten() ,0,2,3,4);
  table.attach(t.get_widget_links() ,0,1,1,3);
  add(table);
  table.show();
  show_all();

}
void Window::realize_callback(void)
{
  static Gdk_Pixmap pix;
  static Gdk_Bitmap  mask;
  static bool init=false;

  if(!init)
  {
    Gdk_Window  win    = get_window();
    GtkStyle    *style = get_style()->gtkobj();

    pix.create_from_xpm_d(win, mask, Gdk_Color(&style->bg[GTK_STATE_NORMAL]), icon_xpm);

    win.set_icon(win,pix,mask);
    win.set_icon_name("BuZale");

    init=true;
  }
  
  return;
}
int main(int argc, char *argv[])
{
  Gtk::Main m(argc, argv);

  Window window;

  m.run();
           
  return(0);
}


/*</BODY></listing></HTML> */
