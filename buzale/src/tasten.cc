/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 09:48:31 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  01.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Tastenfeld
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
static char VersionID[]="%W% %G%";

#include <gtk--/button.h>
#include <gtk--/label.h>
#include <tasten.hh>
#include <label.hh>
#include <allg.hh>
#include <hilfe.xpm>

using SigC::bind;
using SigC::slot;

static char _a[29]={'B','u','Z','a','L','e',
                    '*','*','*','*','*','*','*','*',
                    'e','L','a','Z','u','B','*',
                    '*','*','*', '*','*','*','*','*'};
static char _b[29]={'A','B','C','D','E','F',
                    'G','H','I','J','K','L','M','N',
                    'O','P','Q','R','S','T','U',
                    'V','W','X', 'Y','Z','Ä','Ö','Ü'};
static char _z[29]={' ',' ',' ',' ',' ',' ',
                    '0','1','2','3','4','5','6','7',
                    '8','9',' ',' ','9','8','7',
                    '6','5','4', '3','2','1','0',' '};
Tasten::Tasten() : SigC::Object(), akt_hilfe(-1)
{
  akt = _a;
  for(gint i=0; i<29; i++)
  {
    string text(1,akt[i]);

    label [i] = new Label(text,1,(i%3)+1);
    button[i] = new Button(5);

    button[i]->add(*label[i]);
    button[i]->set_usize(60,60);
    button[i]->clicked.connect(bind<gint>(slot(this,&Tasten::callback_taste),i));
  }

  pixmap = new Gtk::Pixmap(hilfe_xpm);

  button[29] = new Button;
  button[29]->add(*pixmap);
  button[29]->clicked.connect(slot(this,&Tasten::callback_hilfe));
  
  for(gint i=0; i<6; i++)
    oben.pack_start(*button[i]);
  oben.pack_start(*button[29]);
  for(gint i=6; i<14; i++)
    rechts.pack_start(*button[i]);
  for(gint i=14; i<21; i++)
    unten.pack_end(*button[i]);
  for(gint i=21; i<29; i++)
    links.pack_end(*button[i]);
}
Tasten::~Tasten()
{
  delete pixmap;
  for(gint i=0; i<29; i++)
  {
    delete label [i];
    delete button[i];
  }  
  delete button[29];
}
void Tasten::set_mode(gint modus)
{
    switch(modus)
  {
    case START:
      akt = _a;
      break;
    case BUCHSTABEN:
      akt = _b;
      break;
    case ZAHLEN:
      akt = _z;
      break;
  }
  for(gint i=0; i<29; i++)
  {
    const string text(1,akt[i]);
    label[i]->set_text(text);
  }
  
  return;
}
void Tasten::callback_taste(gint nr)
{
  Tasten::taste.emit(akt[nr]);
  return;
}
void Tasten::callback_hilfe()
{
  Tasten::hilfe.emit();
  return;
}
Gtk::HBox &Tasten::get_widget_oben()
{
  return(oben);
}
Gtk::HBox &Tasten::get_widget_unten()
{
  return(unten);
}
Gtk::VBox &Tasten::get_widget_links()
{
  return(links);
}
Gtk::VBox &Tasten::get_widget_rechts()
{
  return(rechts);
}
void Tasten::set_hilfe(char buchstabe)
{
  int i;

  if(akt_hilfe >= 0)
    button[akt_hilfe]->default_farbe();

  for(i=0; i<29;i++)
    if(Allg::toupper(buchstabe)==akt[i])
    {
      akt_hilfe = i;
      button[akt_hilfe]->set_farbe(6);
      break;
    }
  if(i>=29)
    akt_hilfe=-1; 
  return;
}
void Tasten::clear_hilfe()
{
  if(akt_hilfe >= 0)
    button[akt_hilfe]->default_farbe();

  akt_hilfe = -1;
  return;
}

/*</BODY></listing></HTML> */
