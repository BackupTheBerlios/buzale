/*<HTML><listing><BODY>                 Time-stamp: <23 Oct 00 19:47:40 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  20.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Definition der Sound-Classe
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_sound
#define _D_sound
static char soundID[]="%W% %G%";

#include <string>
#include <rand.hh>
class Sound
{
private:
  bool test_file(string file);
  Rand zufall_ok;
  Rand zufall_nok;
public:
  Sound();
  void put(string file);
  void ok();
  void nok();
  void level(string level);
};
#endif
/*</BODY></listing></HTML> */
