#ifndef STATIC_FUNC_CPP
#define	STATIC_FUNC_CPP

//////////////////////
// Gtk callback function file
//////////////////////

// includes
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <iostream>

#include "ConstStrings.h"
#include "TextFileReader.h"
#include "FileOperator.h"
#include "ProgramConfig.h"
#include "BufferModificator.h"



////////////////////////////////////////////////////
// All functions in this file:
////////////////////////////////////////////////////

// not working yet - autoscroll
static void onKeyPress(GtkWidget *sender, GdkEventKey *event, GtkTextBuffer *buffer);
////////////////////////////////////////////////////
// FileOperator functions
////////////////////////////////////////////////////
// create a new file
static void newFile(GtkWidget *sender, GtkTextBuffer *buffer);
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
// clear log
static void clearLog(GtkWidget *sender, GtkTextBuffer *log_buffer);
////////////////////////////////////////////////////
// Configuration functions
////////////////////////////////////////////////////
// checkbox keep a certain file function
static void setKeepSome(GtkWidget *sender, ConstStrings *error);
static void setKeepTex(GtkWidget *sender, ConstStrings *error);
static void setKeepLog(GtkWidget *sender, ConstStrings *error);
static void setKeepAux(GtkToggleButton *sender, ConstStrings *error);
static void documentSelectionChanged (GtkComboBoxText *sender, GtkTextBuffer *buffer);

////////////////////////////////////////////////////
// Buffer modification functions
////////////////////////////////////////////////////
static void insertNewSection (GtkButton *sender, GtkTextBuffer *buffer);
static void insertNewSubsection (GtkButton *sender, GtkTextBuffer *buffer);
static void insertFat(GtkTextIter &iter, GtkTextBuffer *buffer);
static void insertTable(GtkButton *sender, GtkTextBuffer *buffer);
static void insertItemization(GtkButton *sender, GtkTextBuffer *buffer);



////////////////////////////////////////////////////
////////////////////////////////////////////////////
// function implementations
////////////////////////////////////////////////////
////////////////////////////////////////////////////

// not working yet
static void onKeyPress(GtkWidget *sender, GdkEventKey *event, GtkAdjustment *adj)
{
    gtk_adjustment_set_value(gtk_adjustment_get_upper(adj)- gtk_adjustment_get_page_size(adj));
}

////////////////////////////////////////////////////
// FileOperator function callers
////////////////////////////////////////////////////

// open a new file
static void newFile(GtkWidget *sender, GtkTextBuffer *buffer)
{
    FileOperator::newFile(buffer);
}
// Save File handler- & helper-functions
static void saveFileAs(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    FileOperator::saveFileAs(textview, error);
}
// Open File handlerfunction
static void openFile(GtkWidget *sender, GtkTextBuffer *buffer)
{
    FileOperator::openFile(buffer);
}
// Check if Saving File is needed
static void checkSaveFile(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    FileOperator::checkSaveFile(textview, error);
}
// Create Tex file
static void createTexFile(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    FileOperator::createTexFile(textview, error);
}
// GoTex handler- & helper-functions
static void goTex(GtkWidget *sender, GtkTextView *textview)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(textview), "error");
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (textview);
    FileOperator::goTex(textview, buffer, error);
}


static void clearLog(GtkWidget* sender, GtkTextBuffer* log_buffer)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(log_buffer), "error");
    FileOperator::clearLog(log_buffer, error);
}


////////////////////////////////////////////////////
// ProgramConfig function callers
////////////////////////////////////////////////////
static void setKeepSome(GtkWidget *sender, ConstStrings *error)
{
    GtkCheckButton *tex_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "tex_check"));
    GtkCheckButton *log_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "log_check"));
    GtkCheckButton *aux_check = GTK_CHECK_BUTTON(g_object_get_data(G_OBJECT(sender), "aux_check"));
    ProgramConfig::setKeepSomeFilesConfig(tex_check, log_check, aux_check, error);
}

static void setKeepTex(GtkWidget *sender, ConstStrings *error)
{
    ProgramConfig::setKeepTexFileConfig(error);
}

static void setKeepLog(GtkWidget *sender, ConstStrings *error)
{
    ProgramConfig::setKeepLogFileConfig(error);
}

static void setKeepAux(GtkToggleButton *sender, ConstStrings *error)
{
    ProgramConfig::setKeepAuxFileConfig(error);
}

// documentclass combobox handler 
static void documentSelectionChanged (GtkComboBoxText *sender, GtkTextBuffer *buffer)
{
    ConstStrings *error = (ConstStrings*) g_object_get_data(G_OBJECT(buffer), "error");
    ProgramConfig::setDocumentClassConfig(sender, buffer, error);
}



//////////////////////////////////////////////
//sidebar button handlers
//
static void insertNewSection (GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::insertNewSection(buffer);
}


static void insertNewSubsection(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::insertNewSubsection(buffer);
}


static void insertFatTags(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::surroundTextSelection(buffer, ConstStrings::marker_fat, ConstStrings::marker_fat_end);
}


static void insertItalTags(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::surroundTextSelection(buffer, ConstStrings::marker_ital, ConstStrings::marker_ital_end);
}


static void insertImage(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::insertNewImage(buffer);
}


// missing: surround table
static void insertTable(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::insertNewTable(buffer);
}


// not working yet
static void insertItemization(GtkButton *sender, GtkTextBuffer *buffer)
{
    BufferModificator::insertItemization(buffer);
}



#endif /* STATIC_FUNC_CPP */