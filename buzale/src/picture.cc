/*<HTML><listing><BODY>                 Time-stamp: <27 Jan 01 22:34:00 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  06.11.200
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Ausgabe von pixmaps
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <gtk--/main.h>
#include <picture.hh>

using SigC::slot;

Picture::Picture(): 
  SigC::Object(),status(true),modus(MOD_DIREKT), steps(10), step(0),zx(0),zy()
{
  return;
}
Picture::~Picture()
{
  return;
}
void Picture::set_window_color(Gdk_Window &window,GdkColor &c)
{
  win = window;
  bgc=c;
  gc_del.create(window);
  gc_del.set_foreground(Gdk_Color(&c));  
}
void Picture::set_pixmap(Gdk_Pixmap &pixmap)
{
  pix = pixmap;
  zy = win.height() > pix.height() ? (win.height() - pix.height())/2 : 0;
  zx = win.width()  > pix.width()  ? (win.width()  - pix.width() )/2 : 0;
  return;
}
void Picture::set_pixmap(const string name)
{
  Gdk_Bitmap mask;
  
  pix.create_from_xpm(win, mask, Gdk_Color(&bgc), name);
  zy = win.height() > pix.height() ? (win.height() - pix.height())/2 : 0;
  zx = win.width()  > pix.width()  ? (win.width()  - pix.width() )/2 : 0;
  return;
}
void Picture::set_pixmap(const gchar * const *data)
{
  Gdk_Bitmap mask;
  
  pix.create_from_xpm_d(win, mask, Gdk_Color(&bgc), data);
  zy = win.height() > pix.height() ? (win.height() - pix.height())/2 : 0;
  zx = win.width()  > pix.width()  ? (win.width()  - pix.width() )/2 : 0;
  return;
}
void Picture::stop(void)
{
  status=false;
  return;
}
void Picture::start(void)
{
  status=true;
  return;
}
void Picture::show(gint modus, gint time, gint steps)
{
  Picture::modus = modus;
  Picture::steps = steps;
  step=0;
  if(status)
  {
    do_show();
    Gtk::Main::timeout.connect(slot(this,&Picture::do_show),time*1000/steps); 
  }
  return;
}
void Picture::clear(gint modus, gint time, gint steps)
{
  Picture::modus = modus;
  Picture::steps = steps;
  step=0;
  if(status)
  {
    do_clear();
    Gtk::Main::timeout.connect(slot(this,&Picture::do_clear),time*1000/steps); 
  }
  return;
}
void Picture::wait(gint time)
{
  step=0;
  if(status)
  {
    Gtk::Main::timeout.connect(slot(this,&Picture::do_wait),time*1000); 
  }
  return;
}
gint Picture::do_show(void)
{
  if(status)
  {
    step++;
    switch(modus)
    {
      case MOD_STREIFEN:
        show_streifen();
        break;
      case MOD_DIREKT:
      default:
        break;
    }
    if(step > steps)
    {
      ende.emit(SHOW);
      // cout << "ENDE SHOW" << endl;
      return(false);
    }
  }
  
  return(status);
}
gint Picture::do_clear(void)
{
  if(status)
  {
    step++;
    switch(modus)
    {
      case MOD_STREIFEN:
        clear_streifen();
        break;
      case MOD_DIREKT:
        clear_direkt();
      default:
        break;
    }

    if(step > steps)
    {
      // cout << "ENDE CLEAR" << endl;
      ende.emit(CLEAR);
      return(false);
    }
    
  }
    
  return(status);
}
gint Picture::do_wait(void)
{
  if(status)
  {
    // cout << "ENDE WAIT" << endl;
    ende.emit(WAIT);
  }
    
  return(false);
}
void Picture::show_streifen(void)
{
  gint h  = pix.height();
  gint sw = pix.width()/steps +1;
  gint w  = sw/steps +1;
  gint ow = w * (step-1);
  for(gint i=0; i < steps; i++)
  {
    gint ox = i*sw + ow;
    win.draw_pixmap(gc_del,pix,ox,0,zx+ox,zy,w,h);
  }
  return;
}
void Picture::clear_streifen(void)
{
  gint h  = pix.height();
  gint sw = pix.width()/steps +1;
  gint w  = sw/steps +1;
  gint ow = w * (step-1);
  for(gint i=0; i < steps; i++)
  {
    gint ox = i*sw + ow;
    win.draw_rectangle(gc_del,1,zx+ox,zy,w,h);
  }
  return;
}
void Picture::clear_direkt(void)
{
  gint h = pix.height();
  gint w = pix.width();

  if(step > steps)
    win.draw_rectangle(gc_del,1,zx,zy,w,h);

  return;
}
//*</BODY></listing></HTML> */
