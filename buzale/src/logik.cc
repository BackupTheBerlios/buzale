/*<HTML><listing><BODY>                 Time-stamp: <27 Jan 01 22:35:11 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  05.09.2000
#  Ersteller    :
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Programmsteuerung
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <ctype.h>
#include <string>
#include <stream.h>
#include <time.h>
#include <config.hh>
#include <logik.hh>
#include <allg.hh>

using SigC::slot;
using SigC::bind;

Logik::Logik(Menu &m,Tasten &t, Fenster &f) : 
             mblock(&m), tblock(&t), fblock(&f), level(START), 
             hilfe(false),zufall(), sound(), akt_punkte(0), 
             bonus(-1), zeit(0)
{
  bblock = &fblock->get_bild();
  cblock = &fblock->get_count();
  zblock = &fblock->get_timer();
  iblock = &fblock->get_input();
  ablock = &fblock->get_intro();
  eblock = &fblock->get_ende();

  tblock->taste.connect(slot(this,&Logik::tasten_click));
  tblock->hilfe.connect(slot(this,&Logik::hilfe_click));
  iblock->geaendert.connect(slot(this,&Logik::input_change));
  bblock->lock_end.connect(slot(this,&Logik::bild_lock));
  cblock->maximum.connect(slot(this,&Logik::next_level));
  zblock->ende.connect(bind<gint>(slot(this,&Logik::set_level),ENDE));
  ablock->taste_zeichen->clicked.connect(bind<gint>(slot(this,&Logik::set_level),DA));
  ablock->taste_zahlen->clicked.connect(bind<gint>(slot(this,&Logik::set_level),MA));
  mblock->Deutsch.activate.connect(bind<gint>(slot(this,&Logik::set_level),DA));
  mblock->Mathe.activate.connect(bind<gint>(slot(this,&Logik::set_level),MA));
  mblock->Punkte.activate.connect(bind<gint>(slot(this,&Logik::set_level),ENDE));
  eblock->quit.connect(slot(this,&Logik::ende_click));
  fblock->show_intro();
  ablock->start();
}

Logik::~Logik()
{
}
void Logik::hilfe_click()
{
  hilfe=true;
  tblock->set_hilfe(akt_name[iblock->get_text().length()]);
  if(akt_punkte)
    akt_punkte--;
  mblock->set_punkte(akt_punkte);
  if(bonus)
    zblock->set_punkte(akt_punkte);
  else
    (*cblock)--;
  iblock->grab_focus();
  sound.put(akt_sound);
  return;
}
void Logik::input_change(string text)
{
  Config conf;
  gint   anz;

  if(bblock->is_lock())
  {
    iblock->loeschen();
    return;
  }
  if(level==START || level==ENDE)
    return;

  anz = wort_comp(text,max_buchstaben);
  if(anz==9999)                    // Alles richtig eingegeben
  {
    if(cblock->no_ende() || bonus)
    {
      bblock->show_label(akt_name);

      next_buchstabe();
      bblock->set_bild(akt_bild);
      tblock->clear_hilfe();

      if(hilfe)
        hilfe=false;
      else
        sound.ok();
    }
    akt_punkte++;
    mblock->set_punkte(akt_punkte);

    if(bonus)
      zblock->set_punkte(akt_punkte);
    else
      (*cblock)++;

  }
  else if(anz >= 0)                // Falsche Eingabe
    Gtk::Main::timeout.connect(bind(slot(this,&Logik::falsche_eingabe),anz),10);
  else
    if(hilfe) 
      tblock->set_hilfe(akt_name[text.length()]);


}
gint Logik::falsche_eingabe(gint anz)
{
  if(akt_punkte)
    akt_punkte--;
  mblock->set_punkte(akt_punkte);

  if(bonus)
    zblock->set_punkte(akt_punkte);
  else
    (*cblock)--;
  
  iblock->show_text(akt_name.substr(0,anz));
  if(hilfe)
    tblock->set_hilfe(akt_name[anz]);
  sound.nok();
  return(0);
}
void Logik::tasten_click(char buchstabe)
{
  if(bblock->is_lock()) return;

  if(level==START || level==ENDE) return;

  iblock->add_buchstabe(buchstabe); 
  iblock->grab_focus();
 
  return;
}
void Logik::bild_lock()
{
  iblock->grab_focus();
  iblock->loeschen();
  return;
}
void Logik::next_buchstabe()
{
  Config conf;
  int    anz     = conf.get_anz_eintraege(level_name);
  int    nr      = zufall.get(anz);
  string eintrag = conf.get_eintrag(level_name,nr );
    
  Allg::TextConvert(eintrag,akt_name,akt_bild,akt_sound);

//   cout << "Levelname   :" << level_name << endl
//        << "Anz Einträge:" << anz << endl
//        << "Zufall-Nr   :" << nr << endl
//        << "Eintrag     :" << eintrag << endl
//        << "Bezeichung  :" << akt_name << endl
//        << "Bild        :" << akt_bild << endl
//        << "Sound       :" << akt_sound << endl;

  return;
}
gint Logik::wort_comp(string text, gint anz_buchstaben)
{
  gint max_akt  = akt_name.length();
  gint max_text = text.length();

  gint max = max_akt < max_text ? max_akt : max_text;
  gint anz;
  gint soll = anz_buchstaben > 0 ? anz_buchstaben : max_akt;

  if(anz_buchstaben > 0)
    max = anz_buchstaben < max ? anz_buchstaben : max;

  if(soll > max_akt)
    soll = max_akt;

  for(anz=0; anz < max; anz++)
    if(Allg::toupper(akt_name[anz])!=Allg::toupper(text[anz]))
      break;

  if(anz==soll)   // Alles richtig 
    return(9999);
 
  if(anz==max)    // Alles richtig, aber noch nicht vollstaendig
    return(-1);

  return(anz);
}
void Logik::set_level(gint nr)
{
  if(nr == level)
    return;

  if(level==START)
  {
    // Start
    if(nr >= DA && nr <= DE)
    {
      // -> Deutsch-Start
      akt_punkte=0;
      mblock->set_punkte(akt_punkte);
      zblock->set_punkte(akt_punkte);
      hilfe=false;
      ablock->stop();
      tblock->set_mode(Tasten::BUCHSTABEN);
      fblock->show_spiel(); 
    }
    if(nr >= MA && nr <= ME)
    {
      // -> Mathe-Start
      akt_punkte=0;
      mblock->set_punkte(akt_punkte);
      zblock->set_punkte(akt_punkte);
      hilfe=false;
      ablock->stop();
      tblock->set_mode(Tasten::ZAHLEN);
      fblock->show_spiel(); 
    }
    if(nr == ENDE)
    {
      // -> Ende
      return;
    }
  }
  else if(level >= MA && level <= ME)
  {
    // Mathe
    if(nr >= DA && nr <= DE)
    {
      // -> Deutsch-Start   
      if(bblock->is_lock()) return;
      akt_punkte=0;
      mblock->set_punkte(akt_punkte);
      zblock->set_punkte(akt_punkte);
      hilfe=false;
      tblock->set_mode(Tasten::BUCHSTABEN);
    }
    if(nr == ENDE)
    {
      // -> Ende
      bblock->stop();
      eblock->load(Ende::MATHE, akt_punkte);
      fblock->show_ende();                  
    }
  }
  else if(level >= DA && level <= DE)
  {
    // Deutsch
    if(nr >= MA && nr <= ME)
    {
      // -> Mathe-Start
      if(bblock->is_lock()) return;
      akt_punkte=0;
      mblock->set_punkte(akt_punkte);
      zblock->set_punkte(akt_punkte);
      hilfe=false;
      tblock->set_mode(Tasten::ZAHLEN);
    }    
    if(nr == ENDE)
    {
      // -> Ende
      bblock->stop();
      eblock->load(Ende::DEUTSCH,akt_punkte);
      fblock->show_ende();                  
    }
  }
  else if(level==ENDE)
  {
    // ENDE
    if(nr >= DA && nr <= DE)
    {
      // -> Deutsch-Start
      hilfe=false;
      eblock->save();
      tblock->set_mode(Tasten::BUCHSTABEN);
      fblock->show_spiel();        
    }
    if(nr >= MA && nr <= ME)
    {
      // -> Mathe-Start
      hilfe=false;
      eblock->save();
      tblock->set_mode(Tasten::ZAHLEN);
      fblock->show_spiel();        

    }    
    if(nr==START)
    {
      // -> Intro-Start
      eblock->save();
      fblock->show_intro();                  
      tblock->set_mode(Tasten::START);
      ablock->start();      
    }
  }

  level=nr;
  level_name=get_level_name(level);
  sound.level(level_name);

  if(level > START && level < ENDE)
  {
    Config conf;

    max_buchstaben = conf.get_key_gint(level_name,"AnzZeichen");
    zeit           = conf.get_key_gint(level_name,"Zeit");
    bonus          = conf.get_key_gint(level_name,"Bonus");
    next_buchstabe();
    
    if(bonus)
    {
      fblock->set_spiel(Fenster::TIMER);        
      zblock->start(60);
    }
    else
    {
      fblock->set_spiel(Fenster::COUNTER);        
      cblock->set_count(0);
    }
 
    if(max_buchstaben > 0)
      iblock->set_max_length(max_buchstaben);
    else if(max_buchstaben < 0)
      iblock->set_max_length(15);

    iblock->queue_resize();      

    bblock->set_bild(akt_bild);

    bblock->show_label2(conf.get_key(level_name,"Titel"));
  }

  return;
}
void Logik::next_level()
{
  int new_level = level+1;
  if((level>=DA && level < DE) ||
     (level>=MA && level < ME))
  {
    int new_level = level+1;
    Config conf;

    while( (!(conf.is_section(get_level_name(new_level)))) && new_level<ENDE )
      new_level++;

    set_level(new_level);
  }
  else
    set_level(ENDE);
    
  return;
}
string Logik::get_level_name(gint nr)
{
  switch(nr)
  {
    case START:
      return("START");
      break;
    case DA:
      return("DA");
      break;
    case D1:
      return("D1");
      break;
    case D2:
      return("D2");
      break;
    case D3:
      return("D3");
      break;
    case DE:
      return("DE");
      break;
    case MA:
      return("MA");
      break;
    case M1:
      return("M1");
      break;
    case M2:
      return("M2");
      break;
    case M3:
      return("M3");
      break;
    case ME:
      return("ME");
      break;
    case ENDE:
      return("ENDE");
      break;
  }
}
void Logik::ende_click(void)
{
  set_level(START);
  return;
}
/*</BODY></listing></HTML> */
