/*<HTML><listing><BODY>                 Time-stamp: <25 Nov 00 10:33:43 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  26.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Punkte-Zähler und Anzeige
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_count
#define _D_count
static char countID[]="%W% %G%";

#include <gtk--/box.h>
#include <gtk--/pixmap.h>
#include <sigc++/object.h>
#include <sigc++/signal_system.h>
#include <label.hh>

class Count : public Gtk::VBox
{
private:
  static const gint max_count = 20;
  Gtk::Pixmap *pixmap[max_count];
  Label label;
  gint zaehler;
public:
  Count(gint count);
  ~Count();
  void set_count(gint count);
  bool no_ende();
  Count &operator++(void);
  Count &operator--(void);
  Count &operator++(int);
  Count &operator--(int);
  SigC::Signal0<void> maximum;

};
#endif
/*</BODY></listing></HTML> */
