/*<HTML><listing><BODY>                 Time-stamp: <20 Oct 00 23:08:32 markus>
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
#  Beschreibung : Zufallszahlen
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char VersionID[]="%W% %G%";

#include <stream.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <rand.hh>

Rand::Rand():merker(NULL), max_merker(0), anz_merker(0)
{
  srand(time(0));  
  return;
}
Rand::~Rand()
{
  if(merker) delete merker;
  return;
}
int Rand::get(int max)
{
  int zahl;
  
  if(max_merker!=max && max_merker>0) 
  {
    max_merker = 0;
    delete merker;
  }

  if(!max_merker)
  {
    merker = new bool[max];
    memset(merker,0,sizeof(*merker)*max);
    anz_merker = 0;
    max_merker = max;
  }

  if(anz_merker>=max_merker)
  {
    memset(merker,0,sizeof(bool)*max_merker);
    anz_merker=0;
  }

  for(int i=0; i < 200000; i++)
  {
    zahl = (int) ((double)max_merker*rand()/(RAND_MAX+1.0));
    if(!merker[zahl])
    {
      merker[zahl]=true;
      anz_merker++;
      return(zahl+1);
    }
  }
  
  return(zahl+1);
}
/*</BODY></listing></HTML> */
