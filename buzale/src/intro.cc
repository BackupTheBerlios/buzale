/*<HTML><listing><BODY>                 Time-stamp: <03 Jan 01 14:46:21 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  28.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung :  Intro
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#include <gtk--/style.h>
#include <gtk--/main.h>
#include <gtk--/window.h>

#include <intro.hh>
#include <tdeutsch.xpm>
#include <tmathe.xpm>
#include <allg.hh>
#include <config.hh>
#include <sound.hh>
#include <BuZaLe.xpm>
#include <picture.hh>

static char VersionID[]="%W% %G%";

using SigC::slot;

Intro::Intro():Gtk::Table(2,2), status(false),zufall(),init(false)
{
  draw          = new Gtk::DrawingArea();
  taste_zeichen = new Gtk::Button();
  taste_zahlen  = new Gtk::Button();
  abc_pixmap    = new Gtk::Pixmap(tdeutsch_xpm);
  zahl_pixmap   = new Gtk::Pixmap(tmathe_xpm);

  taste_zeichen->add(*abc_pixmap);
  taste_zahlen->add(*zahl_pixmap);
  attach(*draw,0,2,0,1);
  attach(*taste_zeichen,1,2,1,2,0,0,5);
  attach(*taste_zahlen ,0,1,1,2,0,0,10);
  show_all();
}
Intro::~Intro()
{
  delete draw;
  delete taste_zeichen;
  delete taste_zahlen;
  delete abc_pixmap;
  delete picture;
}
void Intro::start(void)
{
  status=true;
  if(init)
    picture->start();
  //draw->realize.connect(slot(this,&Intro::picture_start));
  Gtk::Main::timeout.connect(slot(this,&Intro::picture_start_timeout),2000);
  return;
}
void Intro::stop(void)
{
  picture->stop();
  status=false;
  return;
}
gint Intro::picture_start_timeout(void)
{
  picture_start();
  return(false);
}
void Intro::picture_start(void)
{
  if(!init)
  {
    picture = new Picture();
    picture->ende.connect(slot(this,&Intro::picture_event));
    init=true;
  }

  GtkStyle   *style = draw->get_style()->gtkobj();
  Gdk_Window  win   = draw->get_window();

  picture->set_window_color(win,style->bg[GTK_STATE_NORMAL]);

  picture->set_pixmap(BuZaLe_xpm);
  picture->show(Picture::MOD_STREIFEN,10,50);
  return;
}
void Intro::picture_event(gint mod)
{
  switch(mod)
  {
    case Picture::SHOW:
      picture->wait(3);
      break;
    case Picture::WAIT:
      //picture->clear(Picture::MOD_DIREKT,1,1);
      picture->clear(Picture::MOD_STREIFEN,2,20);
      break;
    case Picture::CLEAR:
      Config     conf;
      Sound      sound;
      int        anz     = conf.get_anz_eintraege("START");
      int        nr      = zufall.get(anz);
      string     eintrag = conf.get_eintrag("START",nr );

      string     akt_name,akt_bild,akt_sound;

      Allg::TextConvert(eintrag,akt_name,akt_bild,akt_sound);
      picture->set_pixmap(akt_bild);
      sound.put(akt_sound);
     
      picture->show(Picture::MOD_STREIFEN,3,20);
      break;
  }
  return;
}

/*</BODY></listing></HTML> */
