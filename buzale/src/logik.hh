/*<HTML><listing><BODY>                 Time-stamp: <11 Jan 01 20:34:38 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  05.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Definition der Programmsteuerung
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_logik
#define _D_logik
static char logikID[]="%W% %G%";

#include <sigc++/signal_system.h>
#include <string>

#include <menu.hh>
#include <tasten.hh>
#include <fenster.hh>

#include <intro.hh>
#include <bild.hh>
#include <count.hh>
#include <timer.hh>
#include <input.hh>
#include <rand.hh>
#include <sound.hh>

class Logik : public SigC::Object
{
private:
  enum    {START, DA,D1,D2,D3,DE, MA,M1,M2,M3,ME, ENDE};
  gint    level;
  string  level_name;
  gint    max_buchstaben;
  gint    bonus;
  gint    zeit;
  bool    hilfe;
  string  akt_name;
  string  akt_bild;
  string  akt_sound;
  gint    akt_punkte;
protected:
  Menu    *mblock;
  Tasten  *tblock;
  Fenster *fblock;

  Bild    *bblock;
  Count   *cblock;
  Timer   *zblock;
  Input   *iblock;
  Intro   *ablock;
  Ende    *eblock;

  Rand   zufall;
  Sound  sound;
  void   tasten_click(char buchstabe);
  void   hilfe_click();
  void   input_change(string text);
  void   bild_lock();
  void   next_buchstabe();
  gint   wort_comp(string text, gint anz_buchstaben);
  gint   falsche_eingabe(gint anz);
  void   set_level(gint nr);
  string get_level_name(gint nr);
  void   next_level();
  void   ende_click();
public:
  Logik(Menu &m,Tasten &t, Fenster &f);
  ~Logik();
};


#endif
/*</BODY></listing></HTML> */
