/*<HTML><listing><BODY>                 Time-stamp: <24 Sep 00 21:34:59 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  18.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Definition der Label-Klasse
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_label
#define _D_label
static char labelID[]="%W% %G%";

#include <gtk--/label.h>

class Label : public Gtk::Label
{

public:
  static gint rot;
  static gint gruen;
  static gint gelb;
  gint font;
  gint farbe;
  Label(string text, gint font=1, gint farbe=1);
};

#endif
/*</BODY></listing></HTML> */
