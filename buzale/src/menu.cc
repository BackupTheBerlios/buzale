/*<HTML><listing><BODY>                 Time-stamp: <04 Jan 01 16:19:54 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  02.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung :  Menu
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <string>
#include <stream.h>
#include <gtk--/main.h>
#include <gtk--/style.h>
#include <menu.hh>
#include <exit.xpm>
#include <stop.xpm>
#include <mathe.xpm>
#include <deutsch.xpm>

using SigC::slot;

void destroy_main(void)
{
  Gtk::Main::quit();
}

Menu::Menu() : Gtk::MenuBar(), init(false)
{
  realize.connect(slot(this,&Menu::realize_callback));
  Ende.show();
  Mathe.show();
  Deutsch.show();
  append(Ende);
  append(Mathe);
  append(Deutsch);
  append(Punkte);
  Punkte.right_justify();
  show();
  Ende.activate.connect(slot(destroy_main));
}
Menu::~Menu()
{
}
void Menu::realize_callback(void)
{
  if(!init)
  {
    Gdk_Window  win    = get_window();
    GtkStyle    *style = get_style()->gtkobj();

    pix.create_from_xpm_d(win, mask, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          exit_xpm);
    Ende.add_pixlabel(pix,mask,"Ende");

    pix.create_from_xpm_d(win, mask, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          mathe_xpm);
    Mathe.add_pixlabel(pix,mask,"Mathe");

    pix.create_from_xpm_d(win, mask, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          deutsch_xpm);
    Deutsch.add_pixlabel(pix,mask,"Deutsch");

    pix.create_from_xpm_d(win, mask, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          stop_xpm);
    Punkte.add_pixlabel(pix,mask,"Punkte:  ");


    init=true;
  }
  
  return;
}
void Menu::set_punkte(gint punkte)
{
  string s("Punkte: ");
  s.append(dec(punkte));
  Punkte.remove();
  Punkte.add_pixlabel(pix,mask,s);
  
  return;
}
/*</BODY></listing></HTML> */
