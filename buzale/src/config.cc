/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 09:52:11 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  17.10.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Configurations-File
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <stdlib.h>
#include <fstream>
#include <strstream>
#include <config.hh>

Config::Config()
{
  char *t=getenv("HOME");
  if(!t) t = "/tmp";
  filename = t;
  filename += "/.buzale";
}
string Config::get_key(string section, string key)
{
  char buffer[256];
  string output("NoKey");
  string skey = "[" + section + "]";
  string line;
  int    index1,index2;

  open_file();

  while(in.getline(buffer,256))
  {
    line   = buffer;
    index1 = line.find(skey);
    if(index1==line.npos)
      continue;
    while(in.getline(buffer,256))
    {
      line   = buffer;
      index1 = line.find(key);

      if(index1==line.npos)
        continue;

      index2 = line.find('=');

      if(index2==line.npos)
        continue;
      if(index2 <= index1)
        continue;
      output = line.substr(index2+1,256);
      istrstream in2(output.c_str());
      in2 >> ws;
      in2.getline(buffer,256);
      output = buffer;
      string::iterator e = output.end();
      e--;
      while(*e=='\\' && in.getline(buffer,256))
      {
        output.erase(e);
        output += buffer;
        e = output.end();
        e--;
      }

      close_file();
      return(output);
    }
    
  }
  
  close_file();
  return(output);
}
bool Config::is_section(string section)
{
  char buffer[256];
  string skey = "[" + section + "]";
  string line;
  int    index;

  open_file();

  while(in.getline(buffer,256))
  {
    line  = buffer;
    index = line.find(skey);
    if(index==line.npos)
      continue;

    close_file();
    return(true);
  }
  
  close_file();
  return(false);
}
gint Config::get_key_gint(string section, string key)
{
  gint zahl=-1;
  string text = get_key(section,key);
  istrstream is(text.c_str());
  is >> zahl;
  return(zahl);
}
gint Config::get_anz_sound(string key)
{
  char buffer[100];
  gint anz=0;
  string eintrag = get_key("Allgemein",key);
  istrstream in(eintrag.c_str());
  while(in >> buffer)
    anz++;

  return(anz);
}
string Config::get_sound(string key, gint nr)
{
  char buffer[100];
  gint anz;
  string eintrag = get_key("Allgemein",key);
  istrstream in(eintrag.c_str());

  for(anz=0; (anz < nr) && (in >> buffer); anz++);

  return(string(buffer));
}
gint Config::get_anz_eintraege(string section)
{
  char buffer[100];
  gint anz=0;
  string eintrag = get_key(section,"Namen");
  istrstream in(eintrag.c_str());
  while(in >> buffer)
    anz++;

  return(anz);
}
string Config::get_eintrag(string section, gint nr)
{
  char buffer[100];
  gint anz;
  string eintrag = get_key(section,"Namen");
  istrstream in(eintrag.c_str());

  for(anz=0; (anz < nr) && (in >> buffer); anz++);

  return(string(buffer));
}

Gdk_Font  Config::font1;
Gdk_Font  Config::font2;
Gdk_Color Config::color1;
Gdk_Color Config::color2;
Gdk_Color Config::color3;
Gdk_Color Config::color4;
Gdk_Color Config::color5;
Gdk_Color Config::color6;
bool      Config::init_font = false;
bool      Config::init_color = false;

Gdk_Font  &Config::get_font(gint nr)
{
  if(!init_font)
  {
    Config conf;
    string eintrag1 = conf.get_key("Allgemein","Font1");
    string eintrag2 = conf.get_key("Allgemein","Font2");
    Config::font1.create(eintrag1.c_str());
    Config::font2.create(eintrag2.c_str());
    init_font=true;
  }
  if(nr==1)
    return(font1);
  else
    return(font2);
}
Gdk_Color  &Config::get_color(gint nr)
{
  if(!init_color)
  {
    Config conf;
    string eintrag1 = conf.get_key("Allgemein","Color1");
    string eintrag2 = conf.get_key("Allgemein","Color2");
    string eintrag3 = conf.get_key("Allgemein","Color3");
    string eintrag4 = conf.get_key("Allgemein","Color4");
    string eintrag5 = conf.get_key("Allgemein","Color5");
    string eintrag6 = conf.get_key("Allgemein","Color6");
    Config::color1.set(eintrag1.c_str());
    Config::color2.set(eintrag2.c_str());
    Config::color3.set(eintrag3.c_str());
    Config::color4.set(eintrag4.c_str());
    Config::color5.set(eintrag5.c_str());
    Config::color6.set(eintrag6.c_str());
    init_color=true;
    
  }
  switch(nr)
  {
    case  1: return(color1); break;
    case  2: return(color2); break;
    case  3: return(color3); break;
    case  4: return(color4); break;
    case  5: return(color5); break;
    default: return(color6); break;
  } 
}

void Config::default_file()
{
  ofstream out;
#ifdef BUZALEDATA
  string tmp_name(BUZALEDATA);
#else

  char *t=getenv("GNOMEDIR");
  if(!t)  t = "/opt";

  string   tmp_name(t);

  tmp_name += "/share/buzale";
#endif
  out.open(filename.c_str());
  in.open(tmp_name.c_str());

  if(in)
  {
    out << in.rdbuf();
    in.close();
  }

  out.close();

  return;
}
void Config::open_file()
{
  in.open(filename.c_str());
  if(!in)
  {
    default_file();
    in.open(filename.c_str()); 
  }
  return;
}
void Config::close_file()
{
  in.close();
  return;
}
/*</BODY></listing></HTML> */
