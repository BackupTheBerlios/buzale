/*<HTML><listing><BODY>                 Time-stamp: <27 Jan 01 11:47:39 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  31.12.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung :  Ende - Bestenliste mit Punkten
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

#include <stdlib.h>
#include <string>
#include <stream.h>
#include <fstream>
#include <strstream>
#include <gtk--/style.h>
#include <ende.hh>
#include <config.hh>
#include <weiter.xpm>
#include <ende1.xpm>
#include <ende2.xpm>

static char VersionID[]="%W% %G%";

using SigC::slot;

static char **icon[10]={ende2_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm,
                        ende1_xpm};

Ende::Ende():Gtk::VBox(),init(false),
                  unten(),oben(10,12,false), taste()
{
  realize.connect(slot(this,&Ende::realize_callback));

  style_norm = get_style()->copy();
  style_dim  = style_norm->copy();
  GtkStyle    *style = style_dim->gtkobj();

  style_dim->set_base(GTK_STATE_NORMAL,Gdk_Color(&style->bg[GTK_STATE_NORMAL]));

  for(int i=0;i<10;i++)
  {
    pixmap [i]= new Gtk::Pixmap(icon[i]);
    label  [i]= new Gtk::Label("0");
    eingabe[i]= new Gtk::Entry(15);
    eingabe[i]->set_text("?????");
    eingabe[i]->set_editable(false);
    eingabe[i]->set_style(*style_dim);
    eingabe[i]->activate.connect(slot(this,&Ende::quit_callback));
    oben.attach(*pixmap [i] ,0 ,1 ,i,i+1);
    oben.attach(*eingabe[i] ,1 ,11,i,i+1,0,0);
    oben.attach(*label  [i] ,11,12,i,i+1);
  }
  
  taste.clicked.connect(slot(this,&Ende::quit_callback));
  taste.set_usize(200,10);
  unten.pack_end(taste,false,true,10);

  pack_start(oben);
  pack_end(unten);

  for(int i=0;i<10;i++)
  {
    label[i]->show();
    pixmap[i]->show();
    eingabe[i]->show();
  }
  taste.show();
  unten.show();
  oben.show();
  show();
}
Ende::~Ende()
{
  for(int i=0;i<10;i++)
  {
    delete pixmap[i];
    delete eingabe[i];
  }

}
void Ende::realize_callback(void)
{
  if(!init)
  {
    Gdk_Pixmap  pix;
    Gdk_Bitmap  mask;
    Gdk_Window  win    = get_window();
    GtkStyle    *style = get_style()->gtkobj();

    pix.create_from_xpm_d(win, mask, 
                          Gdk_Color(&style->bg[GTK_STATE_NORMAL]), 
                          weiter_xpm);
    taste.add_pixmap(pix,mask);

 
    init=true;
  }
  if(akt_eintrag)
  {
    eingabe[akt_eintrag-1]->grab_focus();
  }
  return;
}

typedef struct
{
  char name[16];
  gint punkte;
} _Daten;

void Ende::load(gint ort, gint punkte)
{
  Ende::ort = ort;
  Config conf;
  ifstream in;


  akt_eintrag=0;

  string name = conf.get_key("ENDE",ort==MATHE ? "Mathe":"Deutsch");

  in.open(name.c_str());
  if(in)
  {
    for(int i=0; i<10 && in;i++)
    {
      _Daten dat;

      memset(&dat,0,sizeof(dat));
      in.read(&dat,sizeof(dat));
      if(!((dat.punkte > punkte) || akt_eintrag))
      {
        akt_eintrag=i+1;
        label  [i]->set_text(dec(punkte));
        eingabe[i]->set_text("");
        eingabe[i]->set_editable(true);
        eingabe[i]->set_style(*style_norm);

        i++;
      }
      if(i<10)
      {
        eingabe[i]->set_text(dat.name);
        label  [i]->set_text(dec(dat.punkte));
        eingabe[i]->set_editable(false);
        eingabe[i]->set_style(*style_dim);
      }
       
    }
    in.close();
  }
  return;
}
void Ende::save(void)
{
  Config conf;
  ofstream out;

  string name = conf.get_key("ENDE",ort==MATHE ? "Mathe":"Deutsch");

  out.open(name.c_str());
  if(out)
  {
    for(int i=0; i<10 && out;i++)
    {
      _Daten dat;
      memset(&dat,0,sizeof(dat));
      istrstream is(label[i]->get_text().c_str());
      int wert;
      is >> wert;
      dat.punkte = wert;
      strncpy(dat.name,eingabe[i]->get_text().c_str(),15);

      out.write(&dat,sizeof(dat));
    }
    out.close();
  }
  return;
}
void Ende::quit_callback(void)
{
  Ende::quit.emit();
  return;
}
/*</BODY></listing></HTML> */
