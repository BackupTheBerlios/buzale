/*<HTML><listing><BODY>                 Time-stamp: <04 Jan 01 16:16:58 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  01.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Tastenfeld
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_tasten
#define _D_tasten
static char tastenID[]="%W% %G%";

#include <gtk--/box.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include <sigc++/object.h>
#include <sigc++/signal_system.h>
#include <label.hh>
#include <button.hh>
#include <string>

class Tasten : public SigC::Object
{
private:
  Gtk::Pixmap *pixmap;
  gint akt_hilfe;
protected:
  void callback_taste(gint nr);
  void callback_hilfe();
  Gtk::HBox   oben,unten;
  Gtk::VBox   rechts,links;
  Button      *button[30];
  Label       *label[29];
  char        *akt;
public:
  enum {START,BUCHSTABEN,ZAHLEN};
  SigC::Signal1<void,char> taste;
  SigC::Signal0<void> hilfe;
  Gtk::HBox &get_widget_oben();
  Gtk::HBox &get_widget_unten();
  Gtk::VBox &get_widget_rechts();
  Gtk::VBox &get_widget_links();
  void set_hilfe(char buchstabe);
  void clear_hilfe();
  void set_mode(gint modus);
  Tasten();
  ~Tasten();
};

#endif
/*</BODY></listing></HTML> */
