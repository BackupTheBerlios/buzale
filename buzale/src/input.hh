/*<HTML><listing><BODY>                 Time-stamp: <11 Oct 00 18:40:56 markus>
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
#  Beschreibung :  Eingabefeld
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_input
#define _D_input
static char inputID[]="%W% %G%";

#include <gtk--/entry.h>
#include <sigc++/object.h>
#include <sigc++/signal_system.h>
#include <string>

class Input : public Gtk::Entry
{

private:
  void callback();
  gint str_lng;
public:
  SigC::Signal1<void,string> geaendert;
  Input(gint max=1);
  void loeschen();
  void show_text(string text);
  void add_buchstabe(char buchstabe);
};

#endif
/*</BODY></listing></HTML> */
