/*<HTML><listing><BODY>                 Time-stamp: <17 Feb 01 09:46:44 markus>
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
#  Beschreibung : Classendefinition fuer das Modul config.cc
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_config
#define _D_config
static char configID[]="%W% %G%";

#include <string>
#include <fstream>
#include <gdk--/font.h>
#include <gdk--/color.h> 

class Config
{
private:
  string filename;
  ifstream in;
  void open_file();
  void close_file();
  void default_file();

  static Gdk_Font font1;
  static Gdk_Font font2;
  static Gdk_Color color1;
  static Gdk_Color color2;
  static Gdk_Color color3;
  static Gdk_Color color4;
  static Gdk_Color color5;
  static Gdk_Color color6;
  static bool init_font;
  static bool init_color;

public:
  bool is_section(string section);
  string get_key(string section, string key);
  gint   get_key_gint(string section, string key);
  gint get_anz_eintraege(string section);
  string get_eintrag(string section, gint nr);
  gint get_anz_sound(string key);
  string get_sound(string key, gint nr);
  static Gdk_Font  &get_font(gint nr);
  static Gdk_Color &get_color(gint nr);
  Config();
};
#endif
/*</BODY></listing></HTML> */
