/*<HTML><listing><BODY>                 Time-stamp: <27 Jan 01 22:33:25 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  05.12.2001
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Zündschnur-Widget
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";
#include <sigc++/signal_system.h>
#include <gtk--/main.h>
#include <zschnur.hh>
#include <zschnur.xpm>
#include <feuer1.xpm>
#include <feuer2.xpm>
#include <feuer3.xpm>

using SigC::slot;

static char **icon[3]={feuer1_xpm,
                        feuer2_xpm,
                        feuer3_xpm};

ZSchnur::ZSchnur(): Gtk::DrawingArea(), init(false), max(100), min(0), akt(95), akt_feuer(0),
  h(0),w(0)
{
  return;
}
ZSchnur::~ZSchnur()
{
  return;
}
gint ZSchnur::expose_event_impl(GdkEventExpose* p0)
{
  if(!init) return(0);

  gint ws,hs,wf,hf;
  gint yp,hp,ywin;
  gint xp,wp,xwin;
  
  gint xa = w*akt/(max-min);
  ws = pix_s.width();
  hs = pix_s.height();
  wf = pix_f[akt_feuer].width();
  hf = pix_f[akt_feuer].height();


  // das noetigste loeschen
  if(wf<w)
    xwin=xa-(wf/2);
  else
    xwin=0;
  win.draw_rectangle(gc,true,xwin,0,-1,-1);

  // Zümdschnur zeichnen
  if(hs < h)
  {
    yp=0; hp=hs; ywin=(h-hs)/2;
  }
  else
  {
    yp=(hs-h)/2; hp=h; ywin=0;
  }

  xp=0;xwin=0;

  while(xwin < xa)
  {
    if((xa-xwin) < ws)
      wp=xa-xwin;
    else
      wp=ws;

    win.draw_pixmap(gc,pix_s,xp,yp,xwin,ywin,wp,hp);
    xwin+=wp;
  }

  // Feuer zeichnen
  if(hf < h)
  {
    yp=0; hp=hf; ywin=(h-hf)/2;
  }
  else
  {
    yp=(hf-h)/2; hp=h; ywin=0;
  }
  if(wf<w)
  {
    xp=0; wp=wf; xwin=xa-(wf/2);
  }
  else
  {
    xp=(wf/2)-xa; wp=w; xwin=0;
  }
  if(akt > min)
    win.draw_pixmap(gc_f[akt_feuer],pix_f[akt_feuer],xp,yp,xwin,ywin,wp,hp);
  
  //  cout << "EXPOSE W:" << w   << "  H:" << h  << endl;
  //  cout << "      Ws:" << ws  << " Hs:" << hs << endl;
  //  cout << "     akt:" << akt << " xa:" << xa << endl;
 return(0);
}
void ZSchnur::realize_impl()
{
  Gtk::DrawingArea::realize_impl();  
  style = get_style()->gtkobj();
  win   = get_window();
  gc.create(win);
  gc.set_foreground(Gdk_Color(&style->bg[GTK_STATE_NORMAL]));  

  pix_s.create_from_xpm_d(win, msk_s, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          zschnur_xpm);

  for(int i=0;i<3;i++)
  {
    pix_f[i].create_from_xpm_d(win, msk_f[i],
                               Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                               icon[i]);
     
    gc_f[i].create(win);
    gc_f[i].set_function(GDK_AND);
    gc_f[i].set_foreground(Gdk_Color(&style->bg[GTK_STATE_NORMAL])); 
    //gc_f[i].set_clip_mask(msk_f[i]);
    //gc_f[i].set_clip_origin(0,0);
     
  }
  init=true;
  // cout << "REALISZE" << endl;
 
  return;
}

void ZSchnur::size_request_impl(GtkRequisition* p0)
{
  p0->width  = 100;
  p0->height = 50;
  
  return;
}
void ZSchnur::size_allocate_impl(GtkAllocation* p0)
{
  Gtk::DrawingArea::size_allocate_impl(p0);
  
  h = p0->height;
  w = p0->width;

  // cout << "size_allocate_impl "<< p0->width << "/" <<  p0->height << endl;
  return;
}
void ZSchnur::start(gint max,gint min,gint akt)
{
  ZSchnur::max = max;
  ZSchnur::min = min;
  ZSchnur::akt = akt;
  flag_start=true;
  Gtk::Main::timeout.connect(slot(this,&ZSchnur::changeFeuer),300);
  expose_event_impl(NULL);
  return;
}
gint ZSchnur::changeFeuer(void)
{
  akt_feuer++;
  if(akt_feuer >=3)
    akt_feuer=0;
  expose_event_impl(NULL);

  return(flag_start);
}
void ZSchnur::stop(void)
{
  flag_start=false;
  return;
}
void ZSchnur::set_akt(gint akt)
{
  ZSchnur::akt=akt;
  expose_event_impl(NULL);
  return;
}
/*</BODY></listing></HTML> */
