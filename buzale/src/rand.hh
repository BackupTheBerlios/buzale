/*<HTML><listing><BODY>                 Time-stamp: <20 Oct 00 21:15:56 markus>
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
#  Beschreibung : Classen-Definition fuer Zufallszahlen
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_rand
#define _D_rand
static char randID[]="%W% %G%";

class Rand
{
private:
  bool *merker;
  int  max_merker;
  int  anz_merker;
public:
  Rand();
  ~Rand();
  int get(int max);
};
#endif
/*</BODY></listing></HTML> */
