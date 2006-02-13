#include <gtk/gtk.h>
#include <R.h>
#ifndef WIN32
#include "R_ext/eventloop.h"
#include <gdk/gdkx.h>
#endif

void
R_gtk_eventHandler(void *userData)
{
    while (gtk_events_pending())
	gtk_main_iteration();  
}

void
R_gtk_setEventHandler()
{
    static InputHandler *h = NULL;
    if(!h)
	h = addInputHandler(R_InputHandlers, ConnectionNumber(GDK_DISPLAY()),
			    R_gtk_eventHandler, -1);
}

/**
  Ensure that gtk is loaded. We may want to leave this to 
  another package, e.g.  RGtk, so that people can add their own 
  options.
 */
void loadGTK()
{
    char **argv; 
    int argc = 1;
    argv = (char **) g_malloc(argc * sizeof(char *));
    argv[0] = g_strdup("R");
    gtk_init(&argc, &argv);
}
