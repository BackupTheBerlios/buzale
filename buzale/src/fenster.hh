/*<HTML><listing><BODY>                 Time-stamp: <13 Jan 01 16:22:56 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  28.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Classendefinition des Hauptfensters
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_fenster
#define _D_fenster

static char fensterID[]="%W% %G%";

#include <gtk--/frame.h>
#include <gtk--/table.h>
#include <bild.hh>
#include <count.hh>
#include <timer.hh>
#include <input.hh>
#include <intro.hh>
#include <ende.hh>

class Fenster : public Gtk::Frame
{
private:
  Input  i;
  Bild   b;
  Count  c;
  Timer  t;
  Gtk::Table spiel;
  Intro      intro;
  Ende       ende;
  gint       smod;
public:
  Input &get_input();
  Count &get_count();
  Timer &get_timer();
  Bild  &get_bild();
  Intro &get_intro();
  Ende &get_ende();
  void show_spiel();
  enum {COUNTER,TIMER};
  void set_spiel(gint mod);
  void show_spiel2();
  void show_intro();
  void show_ende();

  Fenster();
  ~Fenster();
};
#endif
/*</BODY></listing></HTML> */
