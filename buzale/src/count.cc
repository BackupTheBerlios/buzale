/*<HTML><listing><BODY>                 Time-stamp: <13 Jan 01 17:36:42 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  26.09.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Punkte-Zähler und Einzeige
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <count.hh>
#include <count.xpm>
#include <string>
#include <stream.h>

Count::Count(gint count) : Gtk::VBox(), label("0",1,1), zaehler(0)
{
  for(int i=0; i<max_count; i++)
    pixmap[i] = new Gtk::Pixmap(count_xpm);

  pack_end(label,false,false,2);
  set_usize(80,0);
  set_count(count);
  label.show();
}
Count::~Count()
{
  for(int i=0; i<max_count; i++)
    delete pixmap[i];
}
void Count::set_count(gint count)
{
  if(zaehler!=count && count < max_count)
  {
    if(zaehler < count)
      for(;zaehler < count;zaehler++)
      {
        pixmap[zaehler]->show();
        pack_end(*pixmap[zaehler],false,false,2); 
      }  
    else
      for(;zaehler > count;zaehler--)
      {
        remove(*pixmap[zaehler-1]);   
      }
  }
  else if(count >= max_count)
    Count::maximum.emit();
    
  label.set_text(dec(zaehler));
  return;
}
bool Count::no_ende()
{
  if(zaehler == (max_count-1))
    return(false);
  else
    return(true);
}
Count & Count::operator++(void)
{
  set_count(zaehler+1);
  return(*this);
}
Count & Count::operator++(int)
{
  set_count(zaehler+1);
  return(*this);
}
Count & Count::operator--(void)
{
  if(zaehler > 0)
    set_count(zaehler-1);
  return(*this);
}
Count & Count::operator--(int)
{
  if(zaehler > 0)
    set_count(zaehler-1);
  return(*this);
}
/*</BODY></listing></HTML> */
