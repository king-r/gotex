/* 
 * File:   ConstStrings.cpp
 * Author: roli
 * 
 * Created on 31. Januar 2015, 00:57
 */

#include <iostream> // to print error message
#include <string>
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
// marker strings 
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
// strings to be replaced
const std::string ConstStrings::marker_ldots = "...";
const std::string ConstStrings::marker_and = "&";
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

// Error messages
const string ConstStrings::message_file_base = "Error opening basefile.\n";         // EC: 1
const string ConstStrings::message_file_notes = "Error opening notesfile.\n";       // EC: 2
const string ConstStrings::message_file_text = "Error opening Text-file.\n";        // EC: 3
const string ConstStrings::message_file_text_save = "Error saving Text-file.\n";    // EC: 4
const string ConstStrings::message_file_gui = "Error loading GUI-File\n";           // EC: 5
const string ConstStrings::message_document_mode = "Error reading document class\n"; // EC: 6


void ConstStrings::PrintErrorMessage(int code)
{
    switch (code)
    {
        case 1: cout << message_file_base; break;
        case 2: cout << message_file_notes; break;
        case 3: cout << message_file_text; break;
        case 4: cout << message_file_text_save; break;
        case 5: cout << message_file_gui; break;
        case 6: cout << message_document_mode; break;
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

}


ConstStrings::ConstStrings(const ConstStrings& orig) {
}

ConstStrings::~ConstStrings() {
}

