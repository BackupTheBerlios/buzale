/*<HTML><listing><BODY>                 Time-stamp: <11 Nov 00 10:50:51 markus>
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
#  Beschreibung : Classendefinition fur das Intro
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_intro
#define _D_intro
static char introID[]="%W% %G%";

#include <gtk--/table.h>
#include <gtk--/button.h>
#include <gtk--/pixmap.h>
#include <gtk--/drawingarea.h>
#include <rand.hh>
#include <picture.hh>

class Intro : public Gtk::Table
{
private:
  Gtk::DrawingArea *draw;
  Gtk::Pixmap      *abc_pixmap;
  Gtk::Pixmap      *zahl_pixmap;

  Picture          *picture;
  void             picture_event(gint mod);
  void             picture_start(void);
  gint             picture_start_timeout(void);
  bool             status;
  bool             init;
  Rand             zufall;
public:
  Gtk::Button *taste_zeichen;
  Gtk::Button *taste_zahlen;
  Intro();
  ~Intro();
  void start(void);
  void stop(void);
};
#endif
/*</BODY></listing></HTML> */
