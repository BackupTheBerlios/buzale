/*<HTML><listing><BODY>                 Time-stamp: <22 Nov 00 18:01:32 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  2.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Definitionen fuer das Modul bild.cc
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_bild
#define _D_bild
static char bildID[]="%W% %G%";

#include <gtk--/layout.h>
#include <gtk--/pixmap.h>
#include <gtk--/button.h>
#include <gtk--/main.h>
#include <string>
#include <label.hh>
#include <sigc++/object.h>
#include <sigc++/signal_system.h>

class  BildLabelPara
{
public:
  gint dx,dy;
  gint aktx,akty;
  Label text;
  BildLabelPara(string name,gint _dx=8, gint _dy=0 ,gint _aktx=0, gint _akty=50,gint _ifont=2,gint _ifarbe=4);
};

class Bild : public Gtk::Layout
{
private:
  Gtk::Pixmap *main_pixmap;
  bool lock;
  bool back;
  bool back_start;
  gint akt_x,akt_y;
  gint max_x,max_y,norm_x,norm_y;

  gint LabelParaCount;

  string aktBildName;

  gint newBild();

  gint moveLabel(BildLabelPara *para);

public:
  Bild();
  ~Bild();
  void set_bild(string name);
  void show_label(string text);
  void show_label2(string text);
  bool is_lock();
  void stop();
  SigC::Signal0<void> lock_end;
};


#endif
/*</BODY></listing></HTML> */
