/*<HTML><listing><BODY>                 Time-stamp: <25 Sep 00 18:33:02 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  25.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Tasten (farbig...)
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_button
#define _D_button
static char buttonID[]="%W% %G%";

#include <gtk--/button.h>

class Button : public Gtk::Button
{

public:
  gint farbe;
  Button(gint farbe=0);
  Button(string text, gint farbe=0);
  void set_farbe(gint farbe);
  void default_farbe();
};



#endif

/*</BODY></listing></HTML> */
