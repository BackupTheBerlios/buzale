/*<HTML><listing><BODY>                 Time-stamp: <23 Oct 00 19:46:07 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  21.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Allgemeine statische Funktionen
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#include <string>
#include <allg.hh>
#include <config.hh>
static char VersionID[]="%W% %G%";
static char _b[512];
static bool _init=false;
void Allg::TextConvert(string eintrag,string &name, string &file_pixmap,string &file_sound)
{
  Config conf;
  string bpfad = conf.get_key("Allgemein","BildPfad");
  string spfad = conf.get_key("Allgemein","SoundPfad");

  file_pixmap = bpfad + "/" + eintrag + ".xpm";
  file_sound  = spfad + "/" + eintrag + ".wav";

  int index = eintrag.find('.');
  if(index != eintrag.npos)
    name = eintrag.substr(0,index);
  else
    name = eintrag;

  return;
}
char Allg::toupper(char buchstabe)
{
  if(!_init)
  {
    memset(_b,0,sizeof(_b));
    _b['a']='A';
    _b['b']='B';
    _b['c']='C';
    _b['d']='D';
    _b['e']='E';
    _b['f']='F';
    _b['g']='G';
    _b['h']='H';
    _b['i']='I';
    _b['j']='J';
    _b['k']='K';
    _b['l']='L';
    _b['m']='M';
    _b['n']='N';
    _b['o']='O';
    _b['p']='P';
    _b['q']='Q';
    _b['r']='R';
    _b['s']='S';
    _b['t']='T';
    _b['u']='U';
    _b['v']='V';
    _b['w']='W';
    _b['x']='X';
    _b['y']='Y';
    _b['z']='Z';
    _b['ä']='Ä';
    _b['ö']='Ö';
    _b['ü']='Ü';
    _b['Ä']='Ä';
    _b['Ü']='Ü';
    _b['Ö']='Ö';
    _init=true;
  }
  if(_b[buchstabe])
    return(_b[buchstabe]);
  else
    return(buchstabe);    
}
/*</BODY></listing></HTML> */
