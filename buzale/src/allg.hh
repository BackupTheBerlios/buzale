/*<HTML><listing><BODY>                 Time-stamp: <21 Oct 00 11:28:01 markus>
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
#ifndef _D_allg
#define _D_allg
static char allgID[]="%W% %G%";

class Allg
{
public:
  static void TextConvert(string eintrag,string &name, string &file_pixmap,string &file_sound);
  static char toupper(char buchstabe);
};
#endif
/*</BODY></listing></HTML> */
