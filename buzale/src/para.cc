/*<HTML><listing><BODY>                 Time-stamp: <13 Oct 00 22:05:27 markus>
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
#  Beschreibung : Klasse Parameter
#                 Liest aus einem File '.char' aus dem HOME-Verzeichnis
#                 Falls noch nicht vorhanden, wird es aus einer Vorlage erzeugt
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <stdlib.h>
#include <para.hh>
#include <ctype.h>

Para::Para()
{
  char *t=getenv("HOME");
  if(!t) t = "/tmp";
  file_name=t;
  file_name += "/.char";
}
Para::~Para()
{

}
int Para::get_buchstaben_anz()
{
  int anz_buchstaben = 0;

  open_file();
  if(file && search_section("[Buchstaben]"))
    while(next_key())
      anz_buchstaben++;

  close_file();

  return(anz_buchstaben);
}
char Para::get_buchstaben(int index)
{
  char buchstabe=' ';
  const char *zeile=NULL;

  open_file();

  if(file && search_section("[Buchstaben]"))
    for(int i=0;i<=index;i++)
      zeile=next_key();

  if(zeile)
    buchstabe=zeile[0];

  close_file();

  return(buchstabe);
}
int Para::get_buchstaben_eintrag_anz(int index)
{
  int anz=0;
  const char *zeile=NULL;

  open_file();

  if(file && search_section("[Buchstaben]"))
    for(int i=0;i<=index;i++)
      zeile=next_key();

  if(zeile)
  {
    bool weiter;
    const char *c=zeile,*c2;
  
    while(*c && isalpha(*c)) c++;
    while(*c && isspace(*c)) c++;
    if(*c) c++;
    
    do
    {
      weiter=false;
      while(*c)
      {
        while(*c && (isspace(*c) || !isalpha(*c))) c++;
        c2=c;
        while(*c2 && isalpha(*c2)) c2++;

        if(!*c2 && (c2[-1]=='\\' || c2[-2]=='\\') )
          weiter=true;
        else if(c2!=c) anz++;

        c=c2;
      }
    }
    while(weiter && (c=next_line())!=NULL);
  }

  close_file();

  return(anz);
}
string Para::get_buchstaben_eintrag(int index_buchstabe, int index_eintrag)
{
  int anz=0;
  const char *zeile=NULL;
  static char buffer[200], *pbuffer=NULL;

  open_file();

  if(file && search_section("[Buchstaben]"))
    for(int i=0;i<=index_buchstabe;i++)
      zeile=next_key();

  if(zeile)
  {
    bool weiter;
    const char *c=zeile,*c2;
    char *c3;
  
    while(*c && isalpha(*c)) c++;
    while(*c && isspace(*c)) c++;
    if(*c) c++;
    
    do
    {
      weiter=false;
      while(*c && anz <= index_eintrag)
      {
        while(*c && (isspace(*c) || !isalpha(*c))) c++;
        c2=c;
        c3=buffer;
        while(*c2 && isalpha(*c2)) 
        {
          *c3=*c2;
          c2++;
          c3++;
        }
        *c3='\0';

        if(!*c2 && (c2[-1]=='\\' || c2[-2]=='\\') )
          weiter=true;
        else if(c2!=c)
          anz++;

        c=c2;
      }
    }
    while(weiter && (c=next_line())!=NULL);
  }

  close_file();
  
  if(anz-1!=index_eintrag)
    memset(buffer,0,sizeof(buffer));

  pbuffer = buffer;
    
  return(pbuffer);
}
string Para::get_root_dir()
{
  const char *zeile;
  static char sbuffer[200],*pbuffer=NULL;
  char *c,buffer[200];
  
  open_file();

  if(file && search_section("[Allgemein]"))
    while(zeile = next_key())
    {
      if(strstr(zeile,"ROOT")==zeile)
      {
        zeile += strlen("ROOT");
        while(*zeile && (isspace(*zeile) || *zeile=='=')) zeile++;
        c=buffer;
        while(*zeile && (isalpha(*zeile) || *zeile=='/' || *zeile=='.'))
        {
          *c=*zeile;
          c++;
          zeile++;
        }
        if(c[-1]!='/')
        {
          *c='/';
          c++;
        }
        *c='\0';
        if(buffer[0]=='.')
        {
          char *pfad = getenv("HOME");
          if(!pfad)
            pfad = "tmp";
          sprintf(sbuffer,"%s%s",pfad,&buffer[1]);
        }
        else
          strcpy(sbuffer,buffer);
        pbuffer = sbuffer;
      }
    }

  close_file();

  return(sbuffer);
}
void Para::open_file()
{
  if(!(file = fopen(file_name.c_str(),"r")))
  {
    default_file();
    file = fopen(file_name.c_str(),"r");
  }
}
void Para::close_file()
{
  if(file) fclose(file);
}
void Para::default_file()
{ 
  FILE *tmp_file;
  char tmp_name[500];
  char *t=getenv("GNOMEDIR");
  if(!t) 
    t = "/opt";
  sprintf(tmp_name,"%s/share/char",t);
  if(tmp_file = fopen(tmp_name,"r"))
  {
    char buffer[1024];
    if(file = fopen(file_name.c_str(),"w"))
    {
      while(int lng=fread(buffer, 1, sizeof(buffer), tmp_file))
        fwrite(buffer,1,lng,file);

      fclose(file);
    }
    
    fclose(tmp_file);
  }
  else
    fclose(fopen(file_name.c_str(),"w"));
}
bool Para::search_section(string name)
{
  if(file)
  {
    char zeile[500];
    while(fgets(zeile, sizeof(zeile),file))
    {
      if(strstr(zeile,name.c_str()) == zeile)
        return(true);
    }
  }
  return(false);
}

bool Para::isKey(string text)
{
  const char *c=text.c_str();
  const char *s=c;

  while(*c && isalpha(*c)) c++;
  if(c!=s)
  {
    while(*c && isspace(*c)) c++;
    if(*c=='=')
      return(true);
  }
  return(false);
}
const char *Para::next_key()
{
  const char *zeile;

  if(file)
    while((zeile=next_line())!=NULL && zeile[0]!='[')
      if(isKey(zeile))
        return(zeile);

  return(NULL);
}
const char *Para::next_line()
{
  static char zeile[500];
  if(file)
  {
    memset(zeile,0,sizeof(zeile));
    return(fgets(zeile, sizeof(zeile),file));
  }
  return(NULL);
}

Gdk_Font  Para::font1;
Gdk_Font  Para::font2;
Gdk_Color Para::color1;
Gdk_Color Para::color2;
Gdk_Color Para::color3;
Gdk_Color Para::color4;
bool      Para::init_font = false;
bool      Para::init_color = false;

Gdk_Font  &Para::get_font(gint nr)
{
  if(!init_font)
  {
    Para::font1.create("-urw-gothic l-demi bold-r-normal--50-481-75-75-p-283-iso8859-1");
    Para::font2.create("-urw-gothic l-book-r-normal--42-401-75-75-p-237-iso8859-1");
    init_font=true;
  }
  if(nr==1)
    return(font1);
  else
    return(font2);
}
Gdk_Color  &Para::get_color(gint nr)
{
  if(!init_color)
  {
    Para::color1.set("medium sea green");
    Para::color2.set("LightGoldenrod1");
    Para::color3.set("indian red");
    Para::color4.set("RoyalBlue4");
    init_color=true;
    
  }
  switch(nr)
  {
    case  1: return(color1); break;
    case  2: return(color2); break;
    case  3: return(color3); break;
    default: return(color4); break;
  } 
}

/*</BODY></listing></HTML> */
