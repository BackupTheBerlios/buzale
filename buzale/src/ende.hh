/*<HTML><listing><BODY>                 Time-stamp: <04 Jan 01 15:59:09 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  31.12.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Classendefinition fur das Intro
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_ende
#define _D_ende
static char endeID[]="%W% %G%";

#include <gtk--/box.h>
#include <gtk--/table.h>
#include <gtk--/entry.h>
#include <gtk--/label.h>
#include <gtk--/pixmap.h>
#include <gtk--/button.h>
#include <gtk--/style.h>
#include <sigc++/signal_system.h>

class Ende : public Gtk::VBox
{
private:
  Gtk::Pixmap      *pixmap[10];
  Gtk::Entry       *eingabe[10];
  Gtk::Label       *label[10];
  Gtk::Table       oben;
  Gtk::HBox        unten;
  Gtk::Style       *style_norm;
  Gtk::Style       *style_dim;  
  Gtk::Button      taste;
  bool             init;
  gint             ort;
  gint             akt_eintrag;

protected:
  void realize_callback(void);
  void quit_callback(void);

public:
  enum {MATHE,DEUTSCH};
  void load(gint ort, gint punkte);
  void save(void);
  SigC::Signal0<void> quit;
  Ende();
  ~Ende();
};
#endif
/*</BODY></listing></HTML> */
