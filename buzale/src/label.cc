/*<HTML><listing><BODY>                 Time-stamp: <18 Oct 00 20:45:35 markus>
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
#  Beschreibung : Label-Modul
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <label.hh>
#include <config.hh>
#include <gtk--/style.h>

Label::Label(string text,gint ifont, gint ifarbe): Gtk::Label(text), font(ifont), farbe(ifarbe)
{
  Gtk::Style *style = get_style()->copy();

  style->set_font(Config::get_font(ifont));
  if(farbe)
    style->set_fg(GTK_STATE_NORMAL,Config::get_color(ifarbe));

  set_style(*style);
}
/*</BODY></listing></HTML> */
