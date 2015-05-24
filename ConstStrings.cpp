/* 
 * File:   ConstStrings.cpp
 * Author: roli
 * 
 * Created on 31. Januar 2015, 00:57
 */

#include <gtk/gtk.h>
#include <iostream> // to print error message
#include <string>
#include <stdlib.h>
#include "ConstStrings.h"

using std::string;
using std::cout;

// configurable strings
const std::string ConstStrings::string_tabulator = "  ";
// shell commands
const string ConstStrings::command_pdflatex = "pdflatex ";
const string ConstStrings::command_pdflatex_parameter = "-shell-escape -interaction=nonstopmode -file-line-error ";
const string ConstStrings::command_pdf_reader = "evince ";
const string ConstStrings::command_remove = "rm";
//filenames
const string ConstStrings::window_title_base = "Gotex";
//filenames
const string ConstStrings::base_filename = "base.txt";
//file endings
const string ConstStrings::file_text_ending = ".txt";
const string ConstStrings::file_tex_ending = ".tex";
const string ConstStrings::file_pdf_ending = ".pdf";
const string ConstStrings::file_aux_ending = ".aux";
const string ConstStrings::file_log_ending = ".log";
const string ConstStrings::file_nav_ending = ".nav";
const string ConstStrings::file_out_ending = ".out";
const string ConstStrings::file_snm_ending = ".snm";
const string ConstStrings::file_toc_ending = ".toc";
//base file markers
const std::string ConstStrings::marker_content = "#STOP#";
const std::string ConstStrings::marker_documentclass = "#DOCUMENTCLASS#";
const std::string ConstStrings::marker_header = "#HEADER#";
const std::string ConstStrings::marker_base_doctitle = "#DOCTITLE#";
const std::string ConstStrings::marker_base_author = "#AUTHOR#";
const std::string ConstStrings::marker_correction_table_columns = "#COLUMNS#";
// marker strings 
const std::string ConstStrings::marker_tex = "#tex";
const std::string ConstStrings::marker_tex_end = "tex#";
const std::string ConstStrings::marker_titlepage = "#titlepage";
const std::string ConstStrings::marker_img = "#img";
const std::string ConstStrings::marker_img_small = "#img small";
const std::string ConstStrings::marker_img_medium = "#img medium";
const std::string ConstStrings::marker_img_big = "#img big";
const std::string ConstStrings::marker_todo_end = "todo#";
const std::string ConstStrings::marker_todo = "#todo";
const std::string ConstStrings::marker_pause = "#pause";
const std::string ConstStrings::marker_subtitle = "#subtitle";
const std::string ConstStrings::marker_title = "#title";
const std::string ConstStrings::marker_frame = "#frame";
const std::string ConstStrings::marker_frame_end = "frame#";
const std::string ConstStrings::marker_center = "#center";
const std::string ConstStrings::marker_center_end = "center#";
const std::string ConstStrings::marker_table = "#table";
const std::string ConstStrings::marker_table_end = "table#";
const std::string ConstStrings::marker_newpage = "#newpage";
const std::string ConstStrings::marker_newline = "#newline";
const std::string ConstStrings::marker_fat = "#fat";
const std::string ConstStrings::marker_fat_end = "fat#";
const std::string ConstStrings::marker_ital = "#ital";
const std::string ConstStrings::marker_ital_end = "ital#";
const std::string ConstStrings::marker_section = "#section";
const std::string ConstStrings::marker_subsection = "#subsection";
const std::string ConstStrings::marker_listentry = "-";
const std::string ConstStrings::marker_doctitle = "#doctitle";
const std::string ConstStrings::marker_author = "#author";
const std::string ConstStrings::marker_math = "#math";
const std::string ConstStrings::marker_math_end = "math#";
const std::string ConstStrings::marker_matharray = "#matharray";
const std::string ConstStrings::marker_matharray_end = "matharray#";
const std::string ConstStrings::marker_matharray_star = "#matharray*";

// strings to be replaced
const std::string ConstStrings::marker_ldots = "...";
const std::string ConstStrings::marker_and = "&";
const std::string ConstStrings::marker_dollar = "$";
const std::string ConstStrings::marker_hashtag = "#";
const std::string ConstStrings::marker_table_column = "|";
const std::string ConstStrings::marker_bigger_than = ">";
const std::string ConstStrings::marker_smaller_than = "<";

// tex-command strings
const std::string ConstStrings::string_titlepage = "\\maketitle";
const std::string ConstStrings::string_img = "\\includegraphics[width=<width>cm]{";
const std::string ConstStrings::string_ldots = "\\ldots";
const std::string ConstStrings::string_todo = "\\todo{";
const std::string ConstStrings::string_pause = "\\pause";
const std::string ConstStrings::string_subtitle = "\\framesubtitle{";
const std::string ConstStrings::string_title = "\\frametitle{";
const std::string ConstStrings::string_article = "article";
const std::string ConstStrings::string_report = "report";
const std::string ConstStrings::string_beamer = "beamer";
const std::string ConstStrings::string_frame = "\\begin{frame}";
const std::string ConstStrings::string_frame_end = "\\end{frame}";
const std::string ConstStrings::string_center = "\\begin{center}";
const std::string ConstStrings::string_center_end = "\\end{center}";
const std::string ConstStrings::string_hline = "\\hline";
const std::string ConstStrings::string_table = "\\begin{tabular}{";
const std::string ConstStrings::string_table_end = "\\end{tabular}";
const std::string ConstStrings::string_newpage = "\\newpage";
const std::string ConstStrings::string_newline = "\\\\";
const std::string ConstStrings::string_begin_textbf = "\\textbf{";
const std::string ConstStrings::string_begin_textit = "\\textit{";
const std::string ConstStrings::string_begin_itemize = "\\begin{itemize}";
const std::string ConstStrings::string_end_itemize = "\\end{itemize}";
const std::string ConstStrings::string_section = "\\section{";
const std::string ConstStrings::string_section_star = "\\section*{";
const std::string ConstStrings::string_subsection = "\\subsection{";
const std::string ConstStrings::string_subsection_star = "\\subsection*{";
const std::string ConstStrings::string_close_bracket = "}";
const std::string ConstStrings::string_and = "\\& ";
const std::string ConstStrings::string_hashtag = "\\#";
const std::string ConstStrings::string_bigger_than = "$>$";
const std::string ConstStrings::string_smaller_than = "$<$";
const std::string ConstStrings::string_item = "\\item";
const std::string ConstStrings::string_displaymath = "\\begin{displaymath}";
const std::string ConstStrings::string_displaymath_end = "\\end{displaymath}";
const std::string ConstStrings::string_eqnarray = "\\begin{eqnarray}";
const std::string ConstStrings::string_eqnarray_star = "\\begin{eqnarray*}";
const std::string ConstStrings::string_eqnarray_end = "\\end{eqnarray}";
const std::string ConstStrings::string_eqnarray_star_end = "\\end{eqnarray*}";


// Log Messages
const string ConstStrings::log_message_type_info = "Info: ";
const string ConstStrings::log_message_type_error = "Error: ";
const string ConstStrings::log_message_type_action = "Action: ";
const string ConstStrings::log_message_type_marker = "Marker: ";
const string ConstStrings::log_message_type_log = "Log: ";

const string ConstStrings::log_message_marker = "---------------------------------------------------";// LC: 0
const string ConstStrings::log_message_opened_file = "Opened file ";                // LC: 1
const string ConstStrings::log_message_saved_file = "Saved file ";                  // LC: 2
const string ConstStrings::log_message_open_pdf_success = "Successfully opened ";   // LC: 3
const string ConstStrings::log_message_open_pdf_failure = "Failed to open Pdf View: ";// LC: 4
const string ConstStrings::log_message_not_need_save_file = " didn't change, no need to save"; //LC: 5
const string ConstStrings::log_message_center_mode_on = "#center was not closed (center# missing)"; //LC: 6
const string ConstStrings::log_message_fat_mode_on = "#fat was not closed (fat# missing)"; //LC: 7
const string ConstStrings::log_message_ital_mode_on = "#ital was not closed (ital# missing)"; //LC: 8
const string ConstStrings::log_message_frame_mode_on = "#frame was not closed (frame# missing)"; //LC: 9
const string ConstStrings::log_message_todo_mode_on = "#todo was not closed (todo# missing)"; //LC: 10
const string ConstStrings::log_message_math_mode_on = "#math was not closed (math# missing)"; 
const string ConstStrings::log_message_matharray_mode_on = "#matharray was not closed (matharray# missing)";
const string ConstStrings::log_message_matharray_star_mode_on = "#matharray* was not closed (matharray# missing)";
const string ConstStrings::log_message_tex_mode_on = "#tex was not closed (tex# misssing)";
const string ConstStrings::log_message_action_gotex = "Started Go Tex!";//LC: 11
const string ConstStrings::log_message_action_tex_created = "Started Tex File Creation!"; //LC: 12
const string ConstStrings::log_message_file_base = "Error opening basefile.";         // LC: 13
const string ConstStrings::log_message_file_notes = "Error opening notesfile.";       // LC: 14
const string ConstStrings::log_message_file_text = "Error opening Text-file.";        // LC: 15
const string ConstStrings::log_message_file_text_save = "Error saving Text-file.";    // LC: 16
const string ConstStrings::log_message_file_gui = "Error loading GUI-File";           // LC: 17
const string ConstStrings::log_message_document_mode = "Error reading document class"; // LC: 18


// DEPRECATED! use PrintLogMessage
void ConstStrings::PrintErrorMessage(int code) // add 12 to error code to get log code
{
    switch (code)
    {
        case 1: cout << log_message_file_base; break;
        case 2: cout << log_message_file_notes; break;
        case 3: cout << log_message_file_text; break;
        case 4: cout << log_message_file_text_save; break;
        case 5: cout << log_message_file_gui; break;
        case 6: cout << log_message_document_mode; break;
    }
}


// PrintLogMessage - adds message into log text view
//
// Codes:
//       0: marker
//       1: standard output/logging mechanism
// >= 1000: error messages
// >= 2000: info messages
// >= 3000: action messages
void ConstStrings::PrintLogMessage(int code, std::string insert)
{
    GtkTextIter iter_end;
    gtk_text_buffer_get_end_iter(log_buffer, &iter_end);
    
    std::string message = "";

    // add message type to message
    addLogMessageType(message, code);
            
    // add log message
    switch(code)
    {
        ///////////////////
		// line marker
        ///////////////////
        case 0: message = message + log_message_marker; break;

        ///////////////////
        // statdard logging mechanism message
        ///////////////////
        case 1: message = message + insert; break;

        ///////////////////
        // Error Messages
        ///////////////////
        // open pdf file failure
        case 1000: message = message + log_message_open_pdf_failure + insert; break;
        // center mode still on
        case 1001: message = message + log_message_center_mode_on; break;
        // fat mode still on
        case 1002: message = message + log_message_fat_mode_on; break;
        // ital mode still on
        case 1003: message = message + log_message_ital_mode_on; break;
        // frame mode still on
        case 1004: message = message + log_message_frame_mode_on; break;
        // todo mode still on
        case 1005: message = message + log_message_todo_mode_on; break;
        // error open base-file
        case 1006: message = message + log_message_file_base; break;
        // error open notes file
        case 1007: message = message + log_message_file_notes; break;
        // error open text file
        case 1008: message = message + log_message_file_text; break;
        // error save text file
        case 1009: message = message + log_message_file_text_save; break;
        // error loading gui file
        case 1010: message = message + log_message_file_gui; break;
        // error loading document class
        case 1011: message = message + log_message_document_mode; break;
        // error math mode still on
        case 1012: message = message + log_message_math_mode_on; break;
        // error matharray mode still on
        case 1013: message = message + log_message_matharray_mode_on; break;
        // error matharray* mode still on
        case 1014: message = message + log_message_matharray_star_mode_on; break;
        // error #tex is still on 
        case 1015: message = message + log_message_tex_mode_on; break;
        
        ///////////////////
        // Info Messages
        ///////////////////
        // saved the current file 
        case 2000: message = message + log_message_saved_file + insert; break;
        // open pdf file success
        case 2001: message = message + log_message_open_pdf_success + insert; break;
        // no need to save file 
        case 2002: message = message + insert + log_message_not_need_save_file; break;
        
        ///////////////////
        // Actions 
        ///////////////////
        // opened a file
        case 3000: message = message + log_message_opened_file + insert; break;        
        // gotex started
        case 3001: message = message + log_message_action_gotex; break;
        // tex file created
        case 3002: message = message + log_message_action_tex_created; break;
    }
    
    message.append("\n");
    
    gtk_text_buffer_insert(log_buffer, &iter_end, message.c_str(), message.size());
		
	//format log_message_type color here TODO

		
	//set scrolledwindow to bottom
	gtk_adjustment_set_value(log_adj, gtk_adjustment_get_upper(log_adj));
	while(gtk_events_pending())
		gtk_main_iteration();
}


void ConstStrings::addLogMessageType(std::string &message, int code)
{
    // divide code to check which type the message is
    int div = code / 1000;

    switch(div)
    {
        case 0: 
            if(code == 0)
            {   message = log_message_type_marker; break; }
            else
            {   message = log_message_type_log; break; }
        case 1:
            message = log_message_type_error; break;
        case 2:
            message = log_message_type_info; break;
        case 3:
            message = log_message_type_action; break;
    }
}


ConstStrings::ConstStrings() {
    flag_ital = false;
    flag_table_mode = false;
    opened_file = "";
    keep_some_files_gtk = false;
    keep_tex_file = true;
    keep_log_file = false;
    keep_aux_file = false;
    
    document_mode = 1;
    
    pdf_viewer_pid = -1;
    
    document_title = "";
    document_author = "";
    
    table_counter = 0;
    
    log_buffer = NULL;
		log_adj = NULL;
    
    error_appeared = false;
    
    // tex conversion modi
    mode_todo = false;
    todo_open_line = 0;
    todo_deep = 0;
    
    mode_fat = false;
    mode_ital = false;
    mode_center = false;
    mode_frame = false;
    mode_math = false;
    mode_matharray = false;
    mode_matharray_star = false;
    mode_inline_math = false;
    
    mode_pure_tex = false;
    
    itemize_last_line = false;
}





ConstStrings::ConstStrings(const ConstStrings& orig) {
}

ConstStrings::~ConstStrings() {
}

