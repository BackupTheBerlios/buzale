/*<HTML><listing><BODY>                 Time-stamp: <22 Nov 00 17:22:54 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  06.11.2000
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Klasse um pixmaps auszugeben
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/
#ifndef _D_picture
#define _D_picture
static char pictureID[]="%W% %G%";

#include <gtk--/window.h>
#include <gtk--/pixmap.h>
#include <sigc++/object.h>
#include <sigc++/signal_system.h>

class Picture : public SigC::Object
{
private:
  Gdk_Pixmap pix;
  Gdk_Window win;
  bool       status;
  gint       zx,zy;
  gint       modus;
  gint       steps,step;
  gint       do_show(void);
  gint       do_clear(void);
  gint       do_wait(void);
  GdkColor   bgc;
  Gdk_GC     gc_del;    
  void       show_streifen(void);
  void       clear_streifen(void);
  void       clear_direkt(void);
public:
  enum {MOD_DIREKT,MOD_STREIFEN};
  enum {SHOW,CLEAR,WAIT};
  Picture();
  ~Picture();
  void stop(void);
  void start(void);
  void show(gint modus, gint time, gint steps);
  void clear(gint modus, gint time, gint steps);
  void wait(gint time);
  void set_pixmap(Gdk_Pixmap &pixmap);
  void set_pixmap(string name);
  void set_pixmap(const gchar * const *data);
  void set_window_color(Gdk_Window &window,GdkColor &bgc);
  SigC::Signal1<void,gint> ende;
};
#endif
/*</BODY></listing></HTML> */
