/*<HTML><listing><BODY>                 Time-stamp: <04 Jan 01 16:13:10 markus>
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
#  Beschreibung : Definition der Classe Menu
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_Menu
#define _D_Menu
static char MenuID[]="%W% %G%";

#include <gtk--/menubar.h>
#include <gtk--/menuitem.h>
#include <gtk--/pixmap.h>

class Menu : public Gtk::MenuBar
{
private:
  Gdk_Pixmap  pix;
  Gdk_Bitmap  mask;  
protected:
  void realize_callback(void);
  bool init;
public:
  Gtk::MenuItem Ende;
  Gtk::MenuItem Mathe;
  Gtk::MenuItem Deutsch;
  Gtk::MenuItem Punkte;
  void set_punkte(gint punkte);
  Menu();
  ~Menu();
};

#endif
/*</BODY></listing></HTML> */
