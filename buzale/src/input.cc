/*<HTML><listing><BODY>                 Time-stamp: <25 Nov 00 12:01:57 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  07.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Eingabefeld
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";


#include <input.hh>
#include <config.hh>
#include <gtk--/style.h>

using SigC::bind;
using SigC::slot;

Input::Input(gint max=1) : Gtk::Entry(max), str_lng(0)
{
  Gtk::Style *style = get_style()->copy();

  style->set_font(Config::get_font(2));
  style->set_fg(GTK_STATE_NORMAL,Config::get_color(3));

  set_style(*style);
  changed.connect(slot(this,&Input::callback));
}
void Input::callback()
{
  string str = get_text();
  if(str.length() > str_lng)
    Input::geaendert.emit(str);
  str_lng = str.length();
  return;
}
void Input::loeschen()
{
  delete_text(0,-1);
  set_position(0);
  str_lng = 0;
  return;
}
void Input::show_text(string text)
{
  str_lng = text.length();
  set_text(text);
  return;
}
void Input::add_buchstabe(char buchstabe)
{
  string str;
  append_text(str=buchstabe);
  return;
}
/*</BODY></listing></HTML> */
