/*<HTML><listing><BODY>                 Time-stamp: <11 Jan 01 19:58:17 markus>
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

static char VersionID[]="%W% %G%";
#include <sigc++/signal_system.h>
#include <gtk--/main.h>
#include <timer.hh>
#include <stream.h>

Timer::Timer(): Gtk::HBox(false,0), label("0"), zschnur(), flag_start(false), akt_time(0)
{
  pack_start(label,false,false,5);
  pack_end(zschnur,true,true,0);
  label.show();
  zschnur.show();
  return;
}
Timer::~Timer()
{
  return;
}
void Timer::set_punkte(gint punkte)
{
  label.set_text(dec(punkte));
  return;
}
void Timer::start(gint sec)
{
  akt_time=sec;
  flag_start=true;
  zschnur.start(akt_time,0,akt_time);
  Gtk::Main::timeout.connect(slot(this,&Timer::countTime),1000);
  return;
}
void Timer::stop()
{
  zschnur.stop();
  flag_start=false;
  return;
}
gint Timer::countTime(void)
{
  akt_time--;
  if(akt_time>=0)
    zschnur.set_akt(akt_time);
  else
  {
    stop();
    Timer::ende.emit();
  }

  return(flag_start);
}
/*</BODY></listing></HTML> */
