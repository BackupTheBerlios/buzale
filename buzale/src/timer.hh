/*<HTML><listing><BODY>                 Time-stamp: <09 Jan 01 21:10:01 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  05.12.2001
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Timer-Widget
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/


#ifndef _D_timer
#define _D_timer

static char timerID[]="%W% %G%";

#include <gtk--/box.h>
#include <gtk--/label.h>
#include <zschnur.hh>
#include <sigc++/signal_system.h>

class Timer: public Gtk::HBox
{
public:
  Timer();
  ~Timer();
  void set_punkte(gint punkte);
  void start(gint sec);
  void stop();
  SigC::Signal0<void> ende;
private:
  bool       flag_start;
  gint       akt_time;
  ZSchnur    zschnur;
  Gtk::Label label;
  gint       countTime(void);
protected:

};
#endif
/*</BODY></listing></HTML> */
