#ifndef STATIC_FUNC_CPP
#define	STATIC_FUNC_CPP

//////////////////////
// Gtk callback function file
//////////////////////

// includes
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <string>
#include <fstream>
#include <stdlib.h> 
#include <iostream>
#include <gtk-2.0/gtk/gtktextbuffer.h>//delete TODO

#include "ConstStrings.h"
#include "TextFileReader.h"



////////////////////////////////////////////////////
// All functions in this file:
////////////////////////////////////////////////////

// not working yet - autoscroll
static void onKeyPress(GtkWidget *sender, GdkEventKey *event, GtkTextBuffer *buffer);
//////////////////////
// file operation functions
// 
// create a new file
static void newFile(GtkWidget *sender, GtkTextBuffer *buffer);
// save a file
static void saveFile(GtkTextView *textview, std::string filename);
// save a file as
static void saveFileAs(GtkWidget *sender, GtkTextView *textview);
// check if saving file is needed
static void checkSaveFile(GtkWidget *sender, GtkTextView *textview);
// open a file
static void openFile(GtkWidget *sender, GtkTextBuffer *buffer);
// generate tex file
static void createTexFile(GtkWidget *sender, GtkTextView *textview);
// go tex - generate tex -> pdflatex -> open pdf in pdfviewer 
static void goTex(GtkWidget *sender, GtkTextView *textview);
// gotex helper functions
static std::string deleteGeneratedBeamerFiles(std::string filename, ConstStrings *error);
static std::string deleteGeneratedFiles(std::string filename, ConstStrings *error);
//////////////////////
// checkbox keep a certain file function
static void setKeepSome(GtkWidget *sender, ConstStrings *error);
static void setKeepTex(GtkWidget *sender, ConstStrings *error);
static void setKeepLog(GtkWidget *sender, ConstStrings *error);
static void setKeepAux(GtkToggleButton *sender, ConstStrings *error);
//////////////////////
// documentclass selector
static void documentSelectionChanged (GtkComboBoxText *sender, GtkTextBuffer *buffer);
//////////////////////
// sidebar buttons
static void insertNewSection (GtkButton *sender, GtkTextBuffer *buffer);
static void insertNewSubsection (GtkButton *sender, GtkTextBuffer *buffer);
static void insertFat(GtkTextIter &iter, GtkTextBuffer *buffer);
static void insertTable(GtkButton *sender, GtkTextBuffer *buffer);
static void insertItemization(GtkButton *sender, GtkTextBuffer *buffer);
// sidebar button helpers
static void getIterAtCursor(GtkTextIter &iter, GtkTextBuffer *buffer);
static void surroundTextSelection(GtkTextBuffer *buffer, std::string text_left, std::string text_right);
// general helpers
static std::string getPathFromFullPath(std::string full_path);
static std::string getFilenameFromFullPath(std::string full_path);


////////////////////////////////////////////////////
// function implementations
////////////////////////////////////////////////////

// not working yet
static void onKeyPress(GtkWidget *sender, GdkEventKey *event, GtkTextBuffer *buffer)
{

}


// open a new file
static void newFile(GtkWidget *sender, GtkTextBuffer *buffer)
{
    gtk_text_buffer_set_text(buffer, "", 0);
    // Get Error & String Handler
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(buffer), "error");
    error->opened_file = "";
}

// Save File handler- & helper-functions
static void saveFileAs(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    error->opened_file = "";
    checkSaveFile(sender, textview);
}


// Open File handlerfunction
static void openFile(GtkWidget *sender, GtkTextBuffer *buffer)
{
    // Get Error & String Handler
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(buffer), "error");
    // open dialog
    GtkWidget *openfiledialog;
    openfiledialog = gtk_file_chooser_dialog_new("Open File", 
                                                NULL, 
                                                GTK_FILE_CHOOSER_ACTION_OPEN, 
                                                "Cancel",
                                                GTK_RESPONSE_CANCEL,
                                                "Open",
                                                GTK_RESPONSE_ACCEPT,
                                                NULL);
    
    gint res = gtk_dialog_run(GTK_DIALOG(openfiledialog));
    if(res == GTK_RESPONSE_ACCEPT)
    {
        // get filename
        char *filen;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (openfiledialog);
        filen = gtk_file_chooser_get_filename (chooser);
        error->opened_file = filen;
        GtkWidget *window = (GtkWidget*) g_object_get_data(G_OBJECT(buffer), "window");
        std::string title = error->window_title_base + " - ";
        title.append(getFilenameFromFullPath(filen));
        gtk_window_set_title(GTK_WINDOW(window), title.c_str());
        gtk_widget_destroy(openfiledialog);

        // read file content
        gchar *content;
        if(! g_file_get_contents(filen, &content, NULL, NULL))
        {
            // prints error "Error loading Text-file.\n"
            error->PrintErrorMessage(3);
        }
        GtkTextIter endOfTextInput, beginOfTextInput;
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &beginOfTextInput);
        gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &endOfTextInput);
        gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &beginOfTextInput, &endOfTextInput);
        
        std::ifstream file(filen);   
        std::string line;
        if(file.is_open())
        {
            while(getline(file, line))
            {
                line = line + "\n";
                GtkTextIter endOfTextInput;
                gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &endOfTextInput);
                gtk_text_buffer_insert(buffer, &endOfTextInput, line.c_str(), -1);
            }
        }
        
        gtk_text_buffer_set_modified (buffer, TRUE);
        
        g_free(content);
        
        // log opened file
        error->PrintLogMessage(1, getFilenameFromFullPath(filen));
    }
    if(res == GTK_RESPONSE_CANCEL)
    {
        gtk_widget_destroy(openfiledialog);
    }
    
}



static void saveFile(GtkTextView *textview, std::string filename)
{    
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    if(filename.find(error->file_text_ending) == std::string::npos)
    {
        filename = filename + error->file_text_ending;
    }
    error->opened_file = filename;
    gtk_widget_set_sensitive (GTK_WIDGET(textview), FALSE);
    // get text buffer
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (textview);
    char *text = NULL;
    // get iterators
    GtkTextIter iter_start, iter_end;
    gtk_text_buffer_get_start_iter (buffer, &iter_start);
    gtk_text_buffer_get_end_iter (buffer, &iter_end);
    // read textview-content
    text = gtk_text_buffer_get_text(buffer, &iter_start, &iter_end, FALSE);
    // save content
    gboolean result = g_file_set_contents(filename.c_str(), text, -1, NULL);
    if (result == FALSE)
    {
    // prints Error: "Error saving Text-file\n"
        error->PrintErrorMessage(4);
    }
    else
    {
        gtk_text_buffer_set_modified (buffer, FALSE);
        error->PrintLogMessage(2, getFilenameFromFullPath(filename));
    }
    g_free(text);
    
    gtk_widget_set_sensitive (GTK_WIDGET(textview), TRUE);
}



static void checkSaveFile(GtkWidget *sender, GtkTextView *textview)
{
    // Get Error & String Handler
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (textview);

    if(gtk_text_buffer_get_modified(buffer) || error->opened_file == "")
    {
        if(error->opened_file == "")
        {
            GtkWidget *savefiledialog;
            savefiledialog = gtk_file_chooser_dialog_new ("Save File as",
                                                    NULL,
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "Cancel", GTK_RESPONSE_CANCEL,
                                                    "Save", GTK_RESPONSE_ACCEPT,
                                                    NULL);
            if (gtk_dialog_run (GTK_DIALOG (savefiledialog)) == GTK_RESPONSE_ACCEPT)
            {
                char *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (savefiledialog));
                GtkWidget *window = (GtkWidget*) g_object_get_data(G_OBJECT(textview), "window");
                std::string window_title = error->window_title_base;
                window_title.append(" - " + getFilenameFromFullPath(filename));
                gtk_window_set_title(GTK_WINDOW(window), window_title.c_str());
                gtk_widget_destroy(savefiledialog);
                saveFile(textview, filename);
            }
            if(gtk_dialog_run (GTK_DIALOG(savefiledialog)) == GTK_RESPONSE_CANCEL)
            {
                return;
            }
        }
        else
        {
            std::string filename = error->opened_file;
            saveFile(textview, filename);
        }
    }
    else
    {
        return;
    }
    
}


// Create Tex file

static void createTexFile(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    checkSaveFile(sender, textview);
    std::string filename = error->opened_file;
    if(filename == "")
        return;
    filename.replace(filename.find(error->file_text_ending), 4, error->file_tex_ending);
    std::string path = getPathFromFullPath(filename);
    path.append("/");
    std::string tempfilename = path.append("tempfile");
    std::ofstream output(tempfilename.c_str(), std::ios::out);
    
    TextFileReader *reader = new TextFileReader();
    const char *c = error->opened_file.c_str();
    reader->ReadBaseFile(output, c, error);
    delete reader;    
    
    output.close();
}


// GoTex handler- & helper-functions
static void goTex(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");

    GtkTextBuffer *buffer = gtk_text_view_get_buffer (textview);

    bool delete_files = 0;
    if(gtk_text_buffer_get_modified(buffer) || error->opened_file == "")
    {
        createTexFile(sender, textview);
        delete_files = 1;
        //gtk_text_buffer_set_modified(buffer, FALSE);
    }
    
    std::string filename = error->opened_file;
    if(filename == "")
        return;
    size_t pos = filename.find(error->file_text_ending);
    filename.replace(pos, 4, error->file_tex_ending);
    
    std::string filename_no_path = getFilenameFromFullPath(filename);
    std::string path = getPathFromFullPath(filename);    
    
    std::string pdfcommand = error->command_pdflatex + error->command_pdflatex_parameter + "-output-directory=" + path + "/ \""
            + filename + "\" | grep \".*:[0-9]*:.*\"";
    
    system(pdfcommand.c_str());
        
    //delete generated tex files
    if (delete_files == 1) 
    {
        filename = deleteGeneratedFiles(filename, error);
        if (error->document_mode == 2) 
        {
            filename = deleteGeneratedBeamerFiles(filename, error);
        }
    }
    else
    {
        filename.replace(filename.find(error->file_tex_ending), error->file_tex_ending.size(), error->file_pdf_ending);
    }
    
    //if pdf is present, open it
    if(FILE *file = fopen(filename.c_str(), "r"))
    {
        fclose(file);
        std::string openpdf = error->command_pdf_reader + filename;
        
        pid_t pid;
        pid = fork();
        
        if(pid == 0)
        {
            system(openpdf.c_str());
            exit(pid);
        }
        else 
        {
            return;
        }
    }
}

/* gotex helpers */
// deletes additional beamer files
static std::string deleteGeneratedBeamerFiles(std::string filename, ConstStrings *error)
{
    filename.replace(filename.find(error->file_pdf_ending), 4, error->file_nav_ending);
    std::string remove_nav = error->command_remove + " " + filename;
    system(remove_nav.c_str());
    
    filename.replace(filename.find(error->file_nav_ending), 4, error->file_out_ending);
    std::string remove_out = error->command_remove + " " + filename;
    system(remove_out.c_str());
    
    filename.replace(filename.find(error->file_out_ending), 4, error->file_snm_ending);
    std::string remove_snm = error->command_remove + " " + filename;
    system(remove_snm.c_str());
    
    filename.replace(filename.find(error->file_snm_ending), 4, error->file_toc_ending);
    std::string remove_toc = error->command_remove + " " + filename;
    system(remove_toc.c_str());
    
    filename.replace(filename.find(error->file_toc_ending), 4, error->file_pdf_ending);
    return filename;
}

// deletes generated files
static std::string deleteGeneratedFiles(std::string filename, ConstStrings *error)
{
    // remove tempfile
    std::string path = getPathFromFullPath(filename);
    std::string removetempfile = error->command_remove + " " + path + "/tempfile";
    system(removetempfile.c_str());
    
    // remove tex file
    if((error->keep_tex_file == false)||(error->keep_some_files_gtk == false))
    {
        std::string removetex = error->command_remove + " " + filename;
        system(removetex.c_str());
    }
    
    // remove aux file
    filename.replace(filename.find(error->file_tex_ending), 4, error->file_aux_ending);
    if((error->keep_aux_file == false)||(error->keep_some_files_gtk == false))
    {
        std::string removeaux = error->command_remove + " " + filename;
        system(removeaux.c_str());
    }

    // remove log file
    filename.replace(filename.find(error->file_aux_ending), 4, error->file_log_ending);
    if((error->keep_log_file == false)||(error->keep_some_files_gtk == false))
    {
        std::string removelog = error->command_remove + " " + filename;
        system(removelog.c_str());
        
    }
    
    // set filename to pdf-file
    filename.replace(filename.find(error->file_log_ending), 4, error->file_pdf_ending);

    return filename;
}

// returns path without the last '/'
static std::string getPathFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(0, pos);
}

//extracts filename from full path
static std::string getFilenameFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(pos+1);
}


// check box handler functions
static void setKeepSome(GtkWidget *sender, ConstStrings *error)
{
    GtkCheckButton *tex_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "tex_check"));
    GtkCheckButton *log_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "log_check"));
    GtkCheckButton *aux_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "aux_check"));
    
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

static void setKeepTex(GtkWidget *sender, ConstStrings *error)
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

static void setKeepLog(GtkWidget *sender, ConstStrings *error)
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

static void setKeepAux(GtkToggleButton *sender, ConstStrings *error)
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


// documentclass combobox handler 
static void documentSelectionChanged (GtkComboBoxText *sender, GtkTextBuffer *buffer)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(buffer), "error");
    gtk_text_buffer_set_modified(buffer, TRUE);
    
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
        error->PrintErrorMessage(6);
    }
}



//sidebar button handlers

static void insertNewSection (GtkButton *sender, GtkTextBuffer *buffer)
{
    // get cursor position
    GtkTextIter iter;
    getIterAtCursor(iter, buffer);
    // set iter to start position of line
    gint row = gtk_text_iter_get_line(&iter);
    gtk_text_iter_set_line(&iter, row);
    // insert "#section" at linebeginning
    gtk_text_buffer_insert(buffer, &iter, (ConstStrings::marker_section + " ").c_str() ,  ConstStrings::marker_section.size() + 1);
    
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
}


static void insertNewSubsection(GtkButton *sender, GtkTextBuffer *buffer)
{
    // get cursor position
    GtkTextIter iter;
    getIterAtCursor(iter, buffer);
    // set iter to start position of line
    gint row = gtk_text_iter_get_line(&iter);
    gtk_text_iter_set_line(&iter, row);
    // insert "#subsection" at linebeginning
    gtk_text_buffer_insert(buffer, &iter, (ConstStrings::marker_subsection + " ").c_str() ,  ConstStrings::marker_subsection.size() + 1);
    
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
    
}


static void insertFatTags(GtkButton *sender, GtkTextBuffer *buffer)
{
    surroundTextSelection(buffer, ConstStrings::marker_fat, ConstStrings::marker_fat_end);
}


static void insertItalTags(GtkButton *sender, GtkTextBuffer *buffer)
{
    surroundTextSelection(buffer, ConstStrings::marker_ital, ConstStrings::marker_ital_end);
}


static void insertImage(GtkButton *sender, GtkTextBuffer *buffer)
{
    // get cursor position
    GtkTextIter iter_cursor, iter;
    getIterAtCursor(iter_cursor, buffer);
    int line_number = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(buffer, &iter, line_number);
    
    // insert image marker
    gtk_text_buffer_insert(buffer, &iter, (ConstStrings::marker_img + " ").c_str(), -1);
    
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}


// missing: surround table
static void insertTable(GtkButton *sender, GtkTextBuffer *buffer)
{
    // get cursor position
    GtkTextIter iter_cursor, iter_insert, iter_line_begin;
    getIterAtCursor(iter_cursor, buffer);
    
    // get iter at cursor line begin and insert newline if needed
    int line_cursor_old = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(buffer, &iter_line_begin, line_cursor_old);
    std::string newline = "\n";
    if(!gtk_text_iter_equal(&iter_cursor, &iter_line_begin))
    {
        gtk_text_buffer_insert_at_cursor(buffer, newline.c_str(), newline.size());
    }
    
    // insert table markers
    gtk_text_buffer_insert_at_cursor(buffer, ConstStrings::marker_table.c_str(), ConstStrings::marker_table.size());
    gtk_text_buffer_insert_at_cursor(buffer, newline.c_str(), newline.size());
    getIterAtCursor(iter_insert, buffer);
    int new_cursor_place_line = gtk_text_iter_get_line(&iter_insert);
    gtk_text_buffer_insert_at_cursor(buffer, newline.c_str(), newline.size());
    gtk_text_buffer_insert_at_cursor(buffer, ConstStrings::marker_table_end.c_str(), ConstStrings::marker_table_end.size());
    
    // place cursor between table
    gtk_text_buffer_get_iter_at_line(buffer, &iter_insert, new_cursor_place_line );
    gtk_text_buffer_place_cursor(buffer, &iter_insert);
    
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
       
}


// not working yet
static void insertItemization(GtkButton *sender, GtkTextBuffer *buffer)
{
    //////////////////////
    /* read needed data */
    
    // get cursor position
    GtkTextIter iter_cursor, iter_cursor_line_begin;
    getIterAtCursor(iter_cursor, buffer);
    // get line of cursor
    int cursor_line = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(buffer, &iter_cursor_line_begin, cursor_line);
    // other variables
    bool itemization_used_repeatedly = false;
    bool itemization_used_in_cursor_line = false;
    int spaces_line_before = 0;
    int spaces_line_cursor = 0;
    
    // check line before cursor
    if(cursor_line > 0)
    {
        GtkTextIter iter_before_cursor;
        gtk_text_buffer_get_iter_at_line(buffer, &iter_before_cursor, cursor_line - 1);
        // count spaces at begin of line
        for(; ((gtk_text_iter_get_char(&iter_before_cursor) == ' ')&&(spaces_line_before < gtk_text_iter_get_chars_in_line(&iter_before_cursor))); spaces_line_before++)
        {
            gtk_text_iter_forward_char(&iter_before_cursor);
        }
        if(gtk_text_iter_get_char(&iter_before_cursor) == '-')
        {
            // itemization is used in line before
            itemization_used_repeatedly = true;
        }
    }
    

    // check cursor line
    gtk_text_buffer_get_iter_at_line(buffer, &iter_cursor_line_begin, cursor_line);
    
    // count space characters in line
    for (; (gtk_text_iter_get_char(&iter_cursor_line_begin) == ' ')&&(spaces_line_cursor < gtk_text_iter_get_chars_in_line(&iter_cursor_line_begin)); spaces_line_cursor++) 
    {
        gtk_text_iter_forward_char(&iter_cursor_line_begin);
    }

    if (gtk_text_iter_get_char(&iter_cursor_line_begin) == '-') 
    {
        // itemization in cursor line present
        itemization_used_in_cursor_line = true;
    }

        
    ///////////////////
    /* evaluate data */
    GtkTextIter iter_insert;
    gtk_text_buffer_get_iter_at_line(buffer, &iter_insert, cursor_line);

    gtk_text_buffer_place_cursor(buffer, &iter_insert);
    
    // case: line == 0 or itemization is not used repeatedly and itemization not used in cursor line
    // --> insert '-', no tabulator possible
    if(((cursor_line == 0)||(!itemization_used_repeatedly))&&!itemization_used_in_cursor_line)
    {
        std::string minus = "- ";
        gtk_text_buffer_insert_at_cursor(buffer, minus.c_str(), 2);
    }
    // case: itemization is used repeatedly and itemization is not used in cursor line
    // --> insert same tabulator as before, then insert '-'
    else if(itemization_used_repeatedly && !itemization_used_in_cursor_line)
    {
        for(int i = 0; i < spaces_line_before; i++)
        {
            std::string space = " ";
            gtk_text_buffer_insert_at_cursor(buffer, space.c_str(), 1);
        }
        std::string minus = "- ";
        gtk_text_buffer_insert_at_cursor(buffer, minus.c_str(), 2);
    }
    // case: itemization is used repeatedly and itemization is used in cursor line
    // --> insert additional tabulator
    else if(itemization_used_repeatedly && itemization_used_in_cursor_line)
    {
        if(spaces_line_before >= spaces_line_cursor)
        {
            // insert tabulator
            gtk_text_buffer_insert_at_cursor(buffer, ConstStrings::string_tabulator.c_str(), ConstStrings::string_tabulator.size());
        }
        else if(spaces_line_before < spaces_line_cursor)
        {
            // delete whole tabulator
            GtkTextIter iter_after_tab = iter_insert;
            for(int i = 0; i < spaces_line_cursor; i++)
            {
                gtk_text_iter_forward_char(&iter_after_tab);
            }
            gtk_text_buffer_delete(buffer, &iter_insert, &iter_after_tab);
            
        }
        
    }
    // case: itemization is not used repeatedly and itemization is used in cursor line
    // --> 
    else if(!itemization_used_repeatedly && itemization_used_in_cursor_line)
    {
        // do nothing
    }

    ///////////////////
    
    // reset cursor
    GtkTextIter resetpos;
    gtk_text_buffer_get_iter_at_line(buffer, &resetpos, cursor_line);
    while(gtk_text_iter_get_char(&resetpos) != '-')
    {
        gtk_text_iter_forward_char(&resetpos);
    }
    gtk_text_iter_forward_char(&resetpos);
    gtk_text_iter_forward_char(&resetpos);
    gtk_text_buffer_place_cursor(buffer, &resetpos);
    
        
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}


// helper functions
static void surroundTextSelection(GtkTextBuffer *buffer, std::string text_left, std::string text_right)
{
    if(gtk_text_buffer_get_has_selection(buffer))
    {
        // set marker strings
        std::string marker_start = " " + text_left + " ";
        std::string marker_end = " " + text_right + " ";
        
        // get selection bounds
        GtkTextIter iter_start, iter_end;
        gtk_text_buffer_get_selection_bounds(buffer, &iter_start, &iter_end);
        
        // insert text
        gtk_text_buffer_insert(buffer, &iter_start, marker_start.c_str(), -1);

        // insert end-marker ( and update selection bound iterators )
        gtk_text_buffer_get_selection_bounds(buffer, &iter_start, &iter_end);
        gtk_text_buffer_insert(buffer, &iter_end, marker_end.c_str(), -1);
        
        // place cursor after end-marker
        gtk_text_buffer_get_selection_bounds(buffer, &iter_start, &iter_end);
        gtk_text_buffer_place_cursor(buffer, &iter_end);
    }
    else
    {
        //error message - nothing selected
        
    }
    
    // focus textview
    GtkTextView *textview = (GtkTextView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}



static void getIterAtCursor(GtkTextIter &iter, GtkTextBuffer *buffer)
{
    GtkTextMark *mark = gtk_text_buffer_get_insert (buffer);
    gtk_text_buffer_get_iter_at_mark(buffer,&iter, mark);
}


static void focusTextView(GtkTextView &log, GtkTextView *textview)
{
    // focus textview
    gtk_widget_grab_focus(GTK_WIDGET(textview));
}

#endif /* STATIC_FUNC_CPP */