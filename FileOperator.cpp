/* 
 * File:   FileOperator.cpp
 * Author: roli
 * 
 * Created on 31. März 2015, 17:31
 */
#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "ConstStrings.h"
#include "FileOperator.h"
#include "TextFileReader.h"
#include "GlobalHelperFunctions.h"

// basic functions
void FileOperator::newFile(GtkTextBuffer *buffer)
{
    gtk_text_buffer_set_text(buffer, "", 0);

    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(buffer), "error");
    error->opened_file = "";
}


void FileOperator::saveFileAs(GtkTextView* textview, ConstStrings *error)
{
    error->opened_file = "";
    checkSaveFile(textview, error);
}


void FileOperator::checkSaveFile(GtkTextView* textview, ConstStrings *error)
{
     // Get Error & String Handler
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
                window_title.append(" - " + GlobalHelperFunctions::getFilenameFromFullPath(filename));
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


void FileOperator::saveFile(GtkTextView *textview, std::string filename)
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
        error->PrintLogMessage(1009, "");
    }
    else
    {
        gtk_text_buffer_set_modified (buffer, FALSE);
        error->PrintLogMessage(0,"");
        error->PrintLogMessage(2000, GlobalHelperFunctions::getFilenameFromFullPath(filename));
    }
    g_free(text);
    
    gtk_widget_set_sensitive (GTK_WIDGET(textview), TRUE);

}


void FileOperator::openFile(GtkTextBuffer* buffer)
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
        title.append(GlobalHelperFunctions::getFilenameFromFullPath(filen));
        gtk_window_set_title(GTK_WINDOW(window), title.c_str());
        gtk_widget_destroy(openfiledialog);

        // read file content
        gchar *content;
        if(! g_file_get_contents(filen, &content, NULL, NULL))
        {
            // prints error "Error loading Text-file.\n"
            //error->PrintErrorMessage(3);
            error->PrintLogMessage(1008, "");
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
        error->PrintLogMessage(0, "");
        error->PrintLogMessage(3000, GlobalHelperFunctions::getFilenameFromFullPath(filen));
    }
    if(res == GTK_RESPONSE_CANCEL)
    {
        gtk_widget_destroy(openfiledialog);
    }
    

}

void FileOperator::createTexFile(GtkTextView* textview, ConstStrings *error)
{
    error->PrintLogMessage(0,"");
    error->PrintLogMessage(3002, "");
    
    checkSaveFile(textview, error);
    std::string filename = error->opened_file;
    if(filename == "")
        return;
    filename.replace(filename.find(error->file_text_ending), 4, error->file_tex_ending);
    std::string path = GlobalHelperFunctions::getPathFromFullPath(filename);
    path.append("/");
    std::string tempfilename = path.append("tempfile");
    std::ofstream output(tempfilename.c_str(), std::ios::out);
    
    TextFileReader *reader = new TextFileReader();
    const char *c = error->opened_file.c_str();
    reader->ReadBaseFile(output, c, error);
    delete reader;    
    
    output.close();
}

void FileOperator::goTex(GtkTextView* textview, GtkTextBuffer *buffer, ConstStrings *error)
{
    error->PrintLogMessage(0,"");
    error->PrintLogMessage(3001, "");
    
    // check if file needs to be saved
    bool delete_files = 0;
    if(gtk_text_buffer_get_modified(buffer) || error->opened_file == "")
    {
        createTexFile(textview, error);
        delete_files = 1;
        //gtk_text_buffer_set_modified(buffer, FALSE);
    }
    else
    {
        error->PrintLogMessage(2002, GlobalHelperFunctions::getFilenameFromFullPath(error->opened_file));
    }
    
    //save tex file in the same path of text file
    std::string filename = error->opened_file;
    if(filename == "")
        return;
    size_t pos = filename.find(error->file_text_ending);
    filename.replace(pos, 4, error->file_tex_ending);
    
    std::string filename_no_path = GlobalHelperFunctions::getFilenameFromFullPath(filename);
    std::string path = GlobalHelperFunctions::getPathFromFullPath(filename);    
    
    
    std::string pdfcommand = error->command_pdflatex + error->command_pdflatex_parameter + "-output-directory=" + path + "/ \""
            + filename + "\" | grep \".*:[0-9]*:.*\"";

    // check for '&' in path here TODO
    //error->PrintLogMessage(1, pdfcommand);
    
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
        error->PrintLogMessage(2001, GlobalHelperFunctions::getFilenameFromFullPath(filename));
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
    else
    {
        error->PrintLogMessage(1000, GlobalHelperFunctions::getFilenameFromFullPath(filename));
    }


}

/* gotex helpers */
// deletes additional beamer files
std::string FileOperator::deleteGeneratedBeamerFiles(std::string filename, ConstStrings *error)
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
std::string FileOperator::deleteGeneratedFiles(std::string filename, ConstStrings *error)
{
    // remove tempfile
    std::string path = GlobalHelperFunctions::getPathFromFullPath(filename);
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


void FileOperator::clearLog(GtkTextBuffer* log_buffer, ConstStrings *error)
{
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(log_buffer, &start);
    gtk_text_buffer_get_end_iter(log_buffer, &end);
    
    gtk_text_buffer_delete(log_buffer, &start, &end);
}

FileOperator::FileOperator() {
}

FileOperator::FileOperator(const FileOperator& orig) {
}

FileOperator::~FileOperator() {
}

