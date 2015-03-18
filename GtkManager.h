/* 
 * File:   gtkManager.h
 * Author: roli
 *
 * Created on 3. Februar 2015, 19:31
 */
#include <gtk/gtk.h>

#include "ConstStrings.h"


#ifndef GTKMANAGER_H
#define	GTKMANAGER_H

// GTK Handler Class
class GtkManager {
public:
    // functions
    void start(int &argc, char** &argv, ConstStrings *error);
    void getWindowResolution(gint &width, gint &height);
    // con- & destructors
    GtkManager();
    GtkManager(const GtkManager& orig);
    virtual ~GtkManager();
private:
    GtkTextBuffer *textbuffer;
    

};

#endif	/* GTKMANAGER_H */

