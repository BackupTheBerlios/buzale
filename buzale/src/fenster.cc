/*<HTML><listing><BODY>                 Time-stamp: <13 Jan 01 16:41:59 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  28.1.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Hautpfenster
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <fenster.hh>

Fenster::Fenster() : Gtk::Frame(), i(), b(), c(0), t(), spiel(3,2), intro(), ende(), smod(-1)
{
  set_usize(450,550);
  spiel.attach(b,1,2,0,1,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND);
  spiel.attach(c,0,1,0,3,0,                  GTK_FILL|GTK_EXPAND);
  spiel.attach(t,1,2,1,2,GTK_FILL|GTK_EXPAND,0,5);
  spiel.attach(i,1,2,2,3,GTK_FILL|GTK_EXPAND,0,5);

  b.show();
  t.show();
  c.show();
  i.show();

  spiel.show();
  intro.show();
  ende.show();
}
Fenster::~Fenster()
{
}
Input &Fenster::get_input()
{
  return(i);
}
Count &Fenster::get_count()
{
  return(c);
}
Timer &Fenster::get_timer()
{
  return(t);
}
Bild &Fenster::get_bild()
{
  return(b);
}
Intro &Fenster::get_intro()
{
  return(intro);
}
Ende &Fenster::get_ende()
{
  return(ende);
}
void Fenster::show_spiel()
{
  remove();
  add(spiel);
  return;
}
void Fenster::set_spiel(gint mod)
{
  if(mod == COUNTER)
  {
    t.hide();
    t.stop();
    c.show();
  }
  if(mod == TIMER)
  {
    c.hide();
    t.show();
  }

  return;
}
void Fenster::show_intro()
{
  remove();
  add(intro);
  return;
}
void Fenster::show_ende()
{
  remove();
  add(ende);
  return;
}

/*</BODY></listing></HTML> */
