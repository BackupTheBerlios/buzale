/*<HTML><listing><BODY>                 Time-stamp: <06 Jan 01 17:41:26 markus>
#$+
#$KL=1
#------------------------------------------------------------------------------
#$+-
#$K
#  Datei        :  %M%
#  Erstellt am  :  05.12.2001
#  Ersteller    :  M.Boller
#  Version      :  %I%
#  vom          :  %G%
#  ID           :  %W%
#  Änderung     :
#$--
#------------------------------------------------------------------------------
#$+
#  Beschreibung : Zündschnur-Widget
#$-
SCCS-Aenderungen werden automatisch angezeigt
*/

static char zschnurID[]="%W% %G%";

#ifndef _D_zschnur
#define _D_zschnur

#include <gtk--/drawingarea.h>
#include <gtk--/pixmap.h>
#include <gtk--/style.h>
#include <gtk--/window.h>

class ZSchnur: public Gtk::DrawingArea
{
public:
  ZSchnur();
  ~ZSchnur();
  void start(gint max,gint min,gint akt);
  void stop();
  void set_akt(gint akt);
private:
  bool       init;
  Gdk_Pixmap pix_s;
  Gdk_Bitmap msk_s;
  Gdk_Pixmap pix_f[3];
  Gdk_Bitmap msk_f[3];
  GdkBitmap  *bitmap[3];
  Gdk_Window win;
  GtkStyle   *style;  
  Gdk_GC     gc;    
  Gdk_GC     gc_f[3];    
  gint       min;
  gint       max;
  gint       akt;
  guint      h;
  guint      w;
  bool       flag_start;
  gint       akt_feuer;
  gint       changeFeuer(void);
protected:
  virtual gint expose_event_impl(GdkEventExpose* p0);
  virtual void realize_impl();
  virtual void size_request_impl(GtkRequisition* p0);
  virtual void size_allocate_impl(GtkAllocation* p0);
};
#endif
/*</BODY></listing></HTML> */
