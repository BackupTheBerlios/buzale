/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 09:44:32 markus>
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
#  Beschreibung : eigene Tasten mit Farbe
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <button.hh>
#include <config.hh>
#include <gdk--/color.h> 
#include <gtk--/style.h>

Button::Button(gint farbe) : Gtk::Button(), farbe(farbe)
{
  default_farbe();
}
Button::Button(string text, gint farbe) : Gtk::Button(text), farbe(farbe)
{
  default_farbe();
}
void Button::set_farbe(gint farbe)
{

  Gtk::Style *style = get_style()->copy();

  if(farbe)
    style->set_bg(GTK_STATE_NORMAL,Config::get_color(farbe));

  set_style(*style);
}
void Button::default_farbe()
{
  set_farbe(farbe);
}
/*</BODY></listing></HTML> */
