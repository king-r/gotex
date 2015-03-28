/* 
 * File:   gtkManager.cpp
 * Author: roli
 * 
 * Created on 3. Februar 2015, 19:31
 */

#include <gtk/gtk.h>
#include <iostream>
#include <string>

#include "GtkManager.h"

#include "static_functions_ui.cpp"


///////////////////////////
// initializing frontend and mapping functions to gtk components
void GtkManager::start(int &argc, char** &argv, ConstStrings *error)
{
    ///////////////////////////
    // init gtk
    ///////////////////////////
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    if (gtk_builder_add_from_file (builder, "ui/gotex_ui.ui", NULL) == 0)
    {
        // prints error message: "Error loading Gui-File\n"
        error->PrintErrorMessage(5);
    }
    

    ///////////////////////////
    // Connecting signal handlers to the constructed widgets.
    ///////////////////////////
    // window
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (builder,"window"));
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), error->window_title_base.c_str());
    // configurate window
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gint width, height;
    getWindowResolution(width, height);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    
    

    ///////////////////////////    
    // text view 
    GtkWidget *textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    g_object_set_data(G_OBJECT(textview), "window", window);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    g_object_set_data(G_OBJECT(buffer), "window", window);
    g_object_set_data(G_OBJECT(buffer), "error", error);
    g_object_set_data(G_OBJECT(buffer), "textview", textview);
    
    //g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(onKeyPress), (gpointer) buffer); 
    
    
    
    // documentclass selector
    GtkComboBoxText *document_selector_combotext = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "documentclass_comboboxtext"));
    g_signal_connect(G_OBJECT(document_selector_combotext), "changed", G_CALLBACK(documentSelectionChanged), (gpointer) buffer);
    
    

    ///////////////////////////
    // menu
    // new file menu entry
    GtkWidget *menuentry_new = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_new"));
    g_object_set_data(G_OBJECT(textview), "error", error);
    g_signal_connect(G_OBJECT(menuentry_new), "activate", G_CALLBACK(newFile), (gpointer) buffer);

    ///////
    // open file menu entry
    GtkWidget *menuentry_open = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_open"));
    g_signal_connect(G_OBJECT(menuentry_open), "activate", G_CALLBACK(openFile), (gpointer) buffer);
    // save file menu entry
    GtkWidget *menuentry_save = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_save"));
    g_signal_connect(G_OBJECT(menuentry_save), "activate", G_CALLBACK(checkSaveFile), (gpointer) textview);
    // save as file menu entry
    GtkWidget *menuentry_save_as = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_save_as"));
    g_signal_connect(G_OBJECT(menuentry_save_as), "activate", G_CALLBACK(saveFileAs), (gpointer) textview);
    // quit menu entry
    GtkWidget *menuentry_quit = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_quit"));
    g_signal_connect(G_OBJECT(menuentry_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);

    ///////
    // mode menu entry
    GtkWidget *menuentry_article = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_article"));
    g_signal_connect(G_OBJECT(menuentry_article), "activate", G_CALLBACK(documentSelectionChanged), (gpointer) buffer);
    GtkWidget *menuentry_report = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_report"));
    g_signal_connect(G_OBJECT(menuentry_report), "activate", G_CALLBACK(documentSelectionChanged), (gpointer) buffer);
    GtkWidget *menuentry_beamer = GTK_WIDGET(gtk_builder_get_object(builder, "menuentry_beamer"));
    g_signal_connect(G_OBJECT(menuentry_beamer), "activate", G_CALLBACK(documentSelectionChanged), (gpointer) buffer);
    
    
    
    ///////////////////////////
    // check boxes
    // tex Check Box
    GtkCheckButton *tex_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "tex_check"));
    g_signal_connect(G_OBJECT(tex_check), "toggled", G_CALLBACK(setKeepTex), (gpointer) error);
    // log Check Box
    GtkCheckButton *log_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "log_check"));
    g_signal_connect(G_OBJECT(log_check), "toggled", G_CALLBACK(setKeepLog), (gpointer) error);
    // aux Check Box
    GtkCheckButton *aux_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "aux_check"));
    g_signal_connect(G_OBJECT(aux_check), "toggled", G_CALLBACK(setKeepAux), (gpointer) error);
        
    // keep some radio button
    GtkRadioButton *keep_some_rad = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "keep_some_rad"));
    g_object_set_data(G_OBJECT(keep_some_rad), "tex_check", tex_check);
    g_object_set_data(G_OBJECT(keep_some_rad), "log_check", log_check);
    g_object_set_data(G_OBJECT(keep_some_rad), "aux_check", aux_check);
    g_signal_connect(G_OBJECT(keep_some_rad), "toggled", G_CALLBACK(setKeepSome), (gpointer) error);
    

    
    ///////////////////////////
    // buttons
    // open file button
    GtkButton *open_file_button = GTK_BUTTON(gtk_builder_get_object(builder, "open_file_button"));
    g_signal_connect(G_OBJECT(open_file_button), "clicked", G_CALLBACK(openFile), (gpointer) buffer);
    // save file button
    GtkButton *save_file_button = GTK_BUTTON(gtk_builder_get_object(builder, "save_file_button"));
    g_signal_connect(G_OBJECT(save_file_button), "clicked", G_CALLBACK(checkSaveFile), (gpointer) textview);
    // create .tex button
    GtkButton *create_tex_button = GTK_BUTTON(gtk_builder_get_object(builder, "create_tex_button"));
    g_signal_connect(G_OBJECT(create_tex_button), "clicked", G_CALLBACK(createTexFile), (gpointer) textview);
    // Gotex button
    GtkButton *go_tex_button = GTK_BUTTON(gtk_builder_get_object(builder, "go_tex_button"));
    g_signal_connect(G_OBJECT(go_tex_button), "clicked", G_CALLBACK(goTex), (gpointer) textview);
   
    /////////////////
    //sidebar buttons
    
    // Header 1 Button
    GtkButton *header1_button = GTK_BUTTON(gtk_builder_get_object(builder, "header1_button"));
    g_signal_connect(G_OBJECT(header1_button), "clicked", G_CALLBACK(insertNewSection), (gpointer) buffer);
    
    // Header 2 Button
    GtkButton *header2_button = GTK_BUTTON(gtk_builder_get_object(builder, "header2_button"));
    g_signal_connect(G_OBJECT(header2_button), "clicked", G_CALLBACK(insertNewSubsection), (gpointer) buffer);
    
    // Fat Button
    GtkButton *fat_button = GTK_BUTTON(gtk_builder_get_object(builder, "fat_button"));
    g_signal_connect(G_OBJECT(fat_button), "clicked", G_CALLBACK(insertFatTags), (gpointer) buffer);
    
    // Ital Button
    GtkButton *ital_button = GTK_BUTTON(gtk_builder_get_object(builder, "ital_button"));
    g_signal_connect(G_OBJECT(ital_button), "clicked", G_CALLBACK(insertItalTags), (gpointer) buffer);
    
    // Image Button
    GtkButton *image_button = GTK_BUTTON(gtk_builder_get_object(builder, "image_button"));
    g_signal_connect(G_OBJECT(image_button), "clicked", G_CALLBACK(insertImage), (gpointer) buffer);
    
    // Table Button
    GtkButton *table_button = GTK_BUTTON(gtk_builder_get_object(builder, "table_button"));
    g_signal_connect(G_OBJECT(table_button), "clicked", G_CALLBACK(insertTable), (gpointer) buffer);
    

    ///////////////////////////
    // finalize gtk
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    
    gtk_main ();

    ///////////////////////////
}


void GtkManager::getWindowResolution(gint &width, gint &height)
{
    GdkScreen *screen = gdk_screen_get_default();
    height = gdk_screen_get_height (screen);
    width  = gdk_screen_get_width (screen);
    gint monitors = gdk_screen_get_n_monitors(screen);
    width = width/(monitors*2);    
}


GtkManager::GtkManager() {
}

GtkManager::GtkManager(const GtkManager& orig) {
}

GtkManager::~GtkManager() {
}

