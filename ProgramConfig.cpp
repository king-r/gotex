/* 
 * File:   ProgramConfig.cpp
 * Author: roli
 * 
 * Created on 31. März 2015, 18:32
 */
#include <string>
#include <gtk/gtk.h>

#include "ConstStrings.h"

#include "ProgramConfig.h"


void ProgramConfig::setKeepSomeFilesConfig(GtkCheckButton *tex_check, GtkCheckButton *log_check, GtkCheckButton *aux_check, ConstStrings* error)
{
    if(error->keep_some_files_gtk == true)
    {
        error->keep_some_files_gtk = false;
        gtk_widget_set_sensitive(GTK_WIDGET(tex_check), false);
        gtk_widget_set_sensitive(GTK_WIDGET(log_check), false);
        gtk_widget_set_sensitive(GTK_WIDGET(aux_check), false);
        
    }
    else
    {    
        error->keep_some_files_gtk = true;
        gtk_widget_set_sensitive(GTK_WIDGET(tex_check), true);
        gtk_widget_set_sensitive(GTK_WIDGET(log_check), true);
        gtk_widget_set_sensitive(GTK_WIDGET(aux_check), true);        
    }
}


void ProgramConfig::setKeepTexFileConfig(ConstStrings* error)
{
    if(error->keep_tex_file == true)
    {
        error->keep_tex_file = false;
    }
    else
    {
        error->keep_tex_file = true;
    }
}


void ProgramConfig::setKeepLogFileConfig(ConstStrings* error)
{
    if(error->keep_log_file == true)
    {
        error->keep_log_file = false;
    }
    else
    {
        error->keep_log_file = true;
    }
}


void ProgramConfig::setKeepAuxFileConfig(ConstStrings* error)
{
    if(error->keep_aux_file == true)
    {
        error->keep_aux_file = false;
    }
    else
    {
        error->keep_aux_file = true;
    }
}

void ProgramConfig::setDocumentClassConfig(GtkComboBoxText* sender, GtkSourceBuffer* buffer, ConstStrings *error)
{
    gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(buffer), TRUE);
    
    const gchar *mode = gtk_combo_box_get_active_id(GTK_COMBO_BOX(sender));
    std::string selection(mode);
    
    if(selection == "selection_article")
    {
        error->document_mode = 1;
    }
    else if(selection == "selection_beamer")
    {
        error->document_mode = 2;
    }
    else if(selection == "selection_report")
    {
        error->document_mode = 3;
    }
    else
    {
        //error->PrintErrorMessage(6);
        error->PrintLogMessage(1011, "");
    }

}


ProgramConfig::ProgramConfig() {
}

ProgramConfig::ProgramConfig(const ProgramConfig& orig) {
}

ProgramConfig::~ProgramConfig() {
}

