/*<HTML><listing><BODY>                 Time-stamp: <07 Oct 00 10:34:27 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  08.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung :  Definition der Parameter-Klasse
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_para
#define _D_para
static char paraID[]="%W% %G%";

#include <stdio.h>
#include <string>
#include <gdk--/font.h>
#include <gdk--/color.h> 

class Para
{
protected:
  FILE   *file;
  string file_name;
  void   open_file();
  void   close_file();
  void   default_file();
  bool   search_section(string name);
  bool   isKey(string text);
  const char *next_key();
  const char *next_line();

  static Gdk_Font font1;
  static Gdk_Font font2;
  static Gdk_Color color1;
  static Gdk_Color color2;
  static Gdk_Color color3;
  static Gdk_Color color4;
  static bool init_font;
  static bool init_color;

public:
  Para();
  ~Para();
  int  get_buchstaben_anz();
  char get_buchstaben(int index_buchstabe);
  int  get_buchstaben_eintrag_anz(int index_buchstabe);
  string get_buchstaben_eintrag(int index_buchstabe, int index_eintrag);
  string get_root_dir();
  static Gdk_Font  &get_font(gint nr);
  static Gdk_Color &get_color(gint nr);

};

#endif
/*</BODY></listing></HTML> */
