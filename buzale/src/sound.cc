/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 10:01:45 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  20.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Soundausgabe
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <string>
#include <fstream>
#include <stdlib.h>
#include <sound.hh>
#include <config.hh>
#include <allg.hh>

Sound::Sound(): zufall_ok()
{
  return;
}
bool Sound::test_file(string file)
{
  ifstream in(file.c_str());
  if(in)
  {
    in.close();
    return(true);
  }  
  in.close();
  return(false);
}
void Sound::put(string file)
{
  if(test_file(file))
  {
    Config conf;
    string aufruf = conf.get_key("Allgemein","SoundPrg") + " " + file + "&";
    system (aufruf.c_str());
  }
  return;
}
void Sound::ok()
{
  Config conf;
  int anz        = conf.get_anz_sound("OK");
  int nr         = zufall_ok.get(anz);
  string eintrag = conf.get_sound("OK",nr);
  string file_sound,file_pixmap,name;
  Allg::TextConvert(eintrag,name,file_pixmap,file_sound);
  put(file_sound);
  return;
}
void Sound::nok()
{
  Config conf;
  int anz        = conf.get_anz_sound("NOK");
  int nr         = zufall_nok.get(anz);
  string eintrag = conf.get_sound("NOK",nr);
  string file_sound,file_pixmap,name;
  Allg::TextConvert(eintrag,name,file_pixmap,file_sound);
  put(file_sound);
  return;
}
void Sound::level(string level)
{
  Config conf;
  string eintrag = conf.get_key(level,"Sound");
  string file_sound,file_pixmap,name;
  Allg::TextConvert(eintrag,name,file_pixmap,file_sound);
  put(file_sound);
  return;
}
/*</BODY></listing></HTML> */
