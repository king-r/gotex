/* 
 * File:   BufferModificator.cpp
 * Author: roli
 * 
 * Created on 31. März 2015, 18:56
 */

#include <gtk/gtk.h>
#include <string>

#include "ConstStrings.h"

#include "BufferModificator.h"

void BufferModificator::insertNewSection(GtkSourceBuffer* buffer)
{
    // get cursor position
    GtkTextIter iter;
    getIterAtCursor(iter, buffer);
    // set iter to start position of line
    gint row = gtk_text_iter_get_line(&iter);
    gtk_text_iter_set_line(&iter, row);
    // insert "#section" at linebeginning
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &iter, (ConstStrings::marker_section + " ").c_str() ,  ConstStrings::marker_section.size() + 1);
    
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
}

void BufferModificator::insertNewSubsection(GtkSourceBuffer* buffer)
{
    // get cursor position
    GtkTextIter iter;
    getIterAtCursor(iter, buffer);
    // set iter to start position of line
    gint row = gtk_text_iter_get_line(&iter);
    gtk_text_iter_set_line(&iter, row);
    // insert "#subsection" at linebeginning
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &iter, (ConstStrings::marker_subsection + " ").c_str() ,  ConstStrings::marker_subsection.size() + 1);
    
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
}

void BufferModificator::insertNewImage(GtkSourceBuffer* buffer)
{
    // get cursor position
    GtkTextIter iter_cursor, iter;
    getIterAtCursor(iter_cursor, buffer);
    int line_number = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter, line_number);
    
    // insert image marker
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &iter, (ConstStrings::marker_img + " ").c_str(), -1);
    
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}

void BufferModificator::insertNewTable(GtkSourceBuffer* buffer)
{
    // get cursor position
    GtkTextIter iter_cursor, iter_insert, iter_line_begin;
    getIterAtCursor(iter_cursor, buffer);
    
    // get iter at cursor line begin and insert newline if needed
    int line_cursor_old = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_line_begin, line_cursor_old);
    std::string newline = "\n";
    if(!gtk_text_iter_equal(&iter_cursor, &iter_line_begin))
    {
        gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), newline.c_str(), newline.size());
    }
    
    // insert table markers
    gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), ConstStrings::marker_table.c_str(), ConstStrings::marker_table.size());
    gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), newline.c_str(), newline.size());
    getIterAtCursor(iter_insert, buffer);
    int new_cursor_place_line = gtk_text_iter_get_line(&iter_insert);
    gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), newline.c_str(), newline.size());
    gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), ConstStrings::marker_table_end.c_str(), ConstStrings::marker_table_end.size());
    
    // place cursor between table
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_insert, new_cursor_place_line );
    gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter_insert);
    
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}

void BufferModificator::insertItemization(GtkSourceBuffer* buffer)
{
    //////////////////////
    /* read needed data */
    
    // get cursor position
    GtkTextIter iter_cursor, iter_cursor_line_begin;
    getIterAtCursor(iter_cursor, buffer);
    // get line of cursor
    int cursor_line = gtk_text_iter_get_line(&iter_cursor);
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_cursor_line_begin, cursor_line);
    // other variables
    bool itemization_used_repeatedly = false;
    bool itemization_used_in_cursor_line = false;
    int spaces_line_before = 0;
    int spaces_line_cursor = 0;
    
    // check line before cursor
    if(cursor_line > 0)
    {
        GtkTextIter iter_before_cursor;
        gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_before_cursor, cursor_line - 1);
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
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_cursor_line_begin, cursor_line);
    
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
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &iter_insert, cursor_line);

    gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter_insert);
    
    // case: line == 0 or itemization is not used repeatedly and itemization not used in cursor line
    // --> insert '-', no tabulator possible
    if(((cursor_line == 0)||(!itemization_used_repeatedly))&&!itemization_used_in_cursor_line)
    {
        std::string minus = "- ";
        gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), minus.c_str(), 2);
    }
    // case: itemization is used repeatedly and itemization is not used in cursor line
    // --> insert same tabulator as before, then insert '-'
    else if(itemization_used_repeatedly && !itemization_used_in_cursor_line)
    {
        for(int i = 0; i < spaces_line_before; i++)
        {
            std::string space = " ";
            gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), space.c_str(), 1);
        }
        std::string minus = "- ";
        gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), minus.c_str(), 2);
    }
    // case: itemization is used repeatedly and itemization is used in cursor line
    // --> insert additional tabulator
    else if(itemization_used_repeatedly && itemization_used_in_cursor_line)
    {
        if(spaces_line_before >= spaces_line_cursor)
        {
            // insert tabulator
            gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer), ConstStrings::string_tabulator.c_str(), ConstStrings::string_tabulator.size());
        }
        else if(spaces_line_before < spaces_line_cursor)
        {
            // delete whole tabulator
            GtkTextIter iter_after_tab = iter_insert;
            for(int i = 0; i < spaces_line_cursor; i++)
            {
                gtk_text_iter_forward_char(&iter_after_tab);
            }
            gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &iter_insert, &iter_after_tab);
            
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
    gtk_text_buffer_get_iter_at_line(GTK_TEXT_BUFFER(buffer), &resetpos, cursor_line);
    while(gtk_text_iter_get_char(&resetpos) != '-')
    {
        gtk_text_iter_forward_char(&resetpos);
    }
    gtk_text_iter_forward_char(&resetpos);
    gtk_text_iter_forward_char(&resetpos);
    gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &resetpos);
    
        
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));

}

void BufferModificator::surroundTextSelection(GtkSourceBuffer* buffer, std::string text_left, std::string text_right)
{
    if(gtk_text_buffer_get_has_selection(GTK_TEXT_BUFFER(buffer)))
    {
        // set marker strings
        std::string marker_start = " " + text_left + " ";
        std::string marker_end = " " + text_right + " ";
        
        // get selection bounds
        GtkTextIter iter_start, iter_end;
        gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(buffer), &iter_start, &iter_end);
        
        // insert text
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &iter_start, marker_start.c_str(), -1);

        // insert end-marker ( and update selection bound iterators )
        gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(buffer), &iter_start, &iter_end);
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer), &iter_end, marker_end.c_str(), -1);
        
        // place cursor after end-marker
        gtk_text_buffer_get_selection_bounds(GTK_TEXT_BUFFER(buffer), &iter_start, &iter_end);
        gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(buffer), &iter_end);
    }
    else
    {
        //error message - nothing selected
        
    }
    
    // focus textview
    GtkSourceView *textview = (GtkSourceView*) g_object_get_data(G_OBJECT(buffer), "textview");
    gtk_widget_grab_focus(GTK_WIDGET(textview));
}

void BufferModificator::getIterAtCursor(GtkTextIter &iter, GtkSourceBuffer *buffer)
{
    GtkTextMark *mark = gtk_text_buffer_get_insert (GTK_TEXT_BUFFER(buffer) );
    gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(buffer), &iter, mark);
}


BufferModificator::BufferModificator() {
}

BufferModificator::BufferModificator(const BufferModificator& orig) {
}

BufferModificator::~BufferModificator() {
}

