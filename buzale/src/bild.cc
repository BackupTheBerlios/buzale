/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 10:08:00 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  02.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Classe für die Aktionsfläche
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <bild.hh>
#include <unistd.h>

using SigC::slot;


Bild::Bild() : Gtk::Layout()
{
  lock=back=false;
  max_x=366;
  max_y=430;
  norm_x=akt_x=500;
  norm_y=akt_y=0;
  set_usize(max_x, max_y);

  main_pixmap = new Gtk::Pixmap();
  put(*main_pixmap,akt_x,akt_y);
}
Bild::~Bild()
{
  delete main_pixmap;
}
void Bild::set_bild(string name)
{
  aktBildName = name;
  back=false;
  akt_x=norm_x;
  akt_y=norm_y;
  newBild();
  return;
}
void Bild::stop()
{
  lock=false;
  return;
}
bool Bild::is_lock()
{
  return(lock);
}

BildLabelPara::BildLabelPara(string name,gint _dx,gint _dy,gint _aktx,gint _akty,gint _ifont,gint _ifarbe):
  text(name,_ifont,_ifarbe), dx(_dx),dy(_dy),aktx(_aktx),akty(_akty) {text.show(); }

void Bild::show_label(string text)
{
  BildLabelPara *par = new BildLabelPara(text,-4,-5,350,450,1,4);
  put(par->text,par->aktx,par->akty);
  show();
  Gtk::Main::timeout.connect(bind(slot(this,&Bild::moveLabel),par),50);
}
void Bild::show_label2(string text)
{
  BildLabelPara *par = new BildLabelPara(text,0,2,80,0,2,3);
  put(par->text,par->aktx,par->akty);
  show();
  Gtk::Main::timeout.connect(bind(slot(this,&Bild::moveLabel),par),60);
}
gint Bild::moveLabel(BildLabelPara *par)
{
  if(par->dx > 0 && par->aktx >= width() ||
     par->dx < 0 && par->aktx <= 0)
  {
    delete par;
    return(false);
  }
  if(par->dy > 0 && par->akty >= height() ||
     par->dy < 0 && par->akty <= 0)
  {
    delete par;
    return(false);
  }
  par->aktx += par->dx;
  par->akty += par->dy;

  move(par->text,par->aktx,par->akty);
  
  return(true);
}
gint Bild::newBild()
{
  if(!back && akt_x==norm_x)
  {
    // Start
    max_x = width();
    max_y = height();
    
    Gtk::Main::timeout.connect(slot(this,&Bild::newBild),40);
    lock=true;
    akt_x--;
  }
  else
  {
    if(lock)
    {
      // Trigger
      if(back)
      {
        if(akt_x > norm_x)
        {
          if(back_start)
          {
            Gdk_Pixmap pixmap;
            Gdk_Bitmap mask;
            main_pixmap->get(pixmap,mask);
            gint wp,hp;
            pixmap.get_size(wp,hp);
            gint w  = width();
            gint h  = height();
            norm_x = w>wp ? w/2-wp/2 : 0;
            akt_y = norm_y = h>hp ? h/2-hp/2 : 0;
            //cout << "Bild x/y:" << wp << "/" << hp << endl;
            //cout << "Fenster x/y:" << w << "/" << h << endl;
            //cout << "Norm x/y:" << norm_x << "/" << norm_y << endl; 
            back_start=false;
          }
          akt_x -= 10;
        }
        else
        {
          back=false;
          lock=false;
          akt_x = norm_x;
          lock_end.emit();
        }
      }
      else
      {
        // altes Bild verschinden lassen
        if(akt_x < max_x)
        {
          akt_x += 5;
        }
        else
        {
          back=true;
          back_start=true;
          main_pixmap->set(aktBildName);   
          main_pixmap->show();   
          norm_x=norm_y=0;
        }
      }
    }
    move(*main_pixmap,akt_x,akt_y);
  }
  return(lock);
}
/*</BODY></listing></HTML> */
