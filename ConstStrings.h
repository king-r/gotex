/* 
 * File:   ConstStrings.h
 * Author: roli
 *
 * Created on 31. Januar 2015, 00:57
 */

#ifndef CONSTSTRINGS_H
#define	CONSTSTRINGS_H
#include <vector>
#include <gtk/gtk.h>

typedef std::vector< std::vector<int> > tableoftables;


class ConstStrings {
public:
    //////////////////////////////////////////
    // const strings
    //////////////////////////////////////////    
    // config strings 
    static const std::string command_remove;
    static const std::string command_pdflatex;
    static const std::string command_pdflatex_parameter;
    static const std::string command_pdf_reader;
    static const std::string base_filename;
    static const std::string window_title_base;
    
    static const std::string file_text_ending;
    static const std::string file_tex_ending;
    static const std::string file_pdf_ending;
    static const std::string file_aux_ending;
    static const std::string file_log_ending;
    static const std::string file_nav_ending;
    static const std::string file_out_ending;
    static const std::string file_snm_ending;
    static const std::string file_toc_ending;
    //
    // configurable strings
    static const std::string string_tabulator;
    // basic file & correction marker-strings
    static const std::string marker_content;
    static const std::string marker_documentclass;
    static const std::string marker_header;
    static const std::string marker_base_doctitle;
    static const std::string marker_base_author;
    static const std::string marker_correction_table_columns;
    // user command marker
    static const std::string marker_tex;
    static const std::string marker_titlepage;
    static const std::string marker_img;
    static const std::string marker_img_small;
    static const std::string marker_img_medium;
    static const std::string marker_img_big;
    static const std::string marker_todo;
    static const std::string marker_todo_end;
    static const std::string marker_pause;
    static const std::string marker_subtitle;
    static const std::string marker_title;
    static const std::string marker_frame;
    static const std::string marker_frame_end;
    static const std::string marker_center;
    static const std::string marker_center_end;
    static const std::string marker_table;
    static const std::string marker_table_end;
    static const std::string marker_newpage;
    static const std::string marker_newline;
    static const std::string marker_ital;
    static const std::string marker_ital_end;
    static const std::string marker_fat;
    static const std::string marker_fat_end;    
    static const std::string marker_section;
    static const std::string marker_listentry; 
    static const std::string marker_subsection;
    static const std::string marker_doctitle;
    static const std::string marker_author;
    static const std::string marker_math;
    static const std::string marker_math_end;
    
    // Strings to be replaced
    static const std::string marker_ldots;
    static const std::string marker_and;
    static const std::string marker_hashtag;    
    static const std::string marker_table_column;    
    static const std::string marker_bigger_than;
    static const std::string marker_smaller_than;
    // Error Messages
    static const std::string log_message_file_base;             // EC: 1
    static const std::string log_message_file_notes;            // EC: 2
    static const std::string log_message_file_text;             // EC: 3
    static const std::string log_message_file_text_save;        // EC: 4
    static const std::string log_message_file_gui;              // EC: 5
    static const std::string log_message_document_mode;         // EC: 6
    // Log Message strings
    static const std::string log_message_type_info;
    static const std::string log_message_type_error;
    static const std::string log_message_type_action;
    static const std::string log_message_type_marker;
    static const std::string log_message_type_log;
    static const std::string log_message_marker;                // LC:  0
    static const std::string log_message_opened_file;           // LC:  1
    static const std::string log_message_saved_file;            // LC:  2
    static const std::string log_message_open_pdf_success;      // LC:  3
    static const std::string log_message_open_pdf_failure;      // LC:  4
    static const std::string log_message_not_need_save_file;    // LC:  5
    static const std::string log_message_center_mode_on;        // LC:  6
    static const std::string log_message_fat_mode_on;           // LC:  7
    static const std::string log_message_ital_mode_on;          // LC:  8
    static const std::string log_message_frame_mode_on;         // LC:  9
    static const std::string log_message_todo_mode_on;          // LC: 10

    static const std::string log_message_action_gotex;          // LC: 11
    static const std::string log_message_action_tex_created;    // LC: 12
    static const std::string log_message_action_opened_file;    // LC: 13
    
    
    // Latex strings
    static const std::string string_titlepage;
    static const std::string string_img;
    static const std::string string_ldots;
    static const std::string string_todo;
    static const std::string string_pause;
    static const std::string string_subtitle;
    static const std::string string_title;
    static const std::string string_report;
    static const std::string string_article;
    static const std::string string_beamer;
    static const std::string string_frame;
    static const std::string string_frame_end;
    static const std::string string_center;
    static const std::string string_center_end;
    static const std::string string_hline;
    static const std::string string_table;
    static const std::string string_table_end;
    static const std::string string_newpage;
    static const std::string string_newline;
    static const std::string string_begin_textit;
    static const std::string string_begin_textbf;
    static const std::string string_section;
    static const std::string string_section_star;
    static const std::string string_subsection;
    static const std::string string_subsection_star;
    static const std::string string_begin_itemize;
    static const std::string string_end_itemize;
    static const std::string string_close_bracket;
    static const std::string string_and;
    static const std::string string_hashtag;
    static const std::string string_bigger_than;
    static const std::string string_smaller_than;
    static const std::string string_item;
    static const std::string string_displaymath;
    //////////////////////////////////////////
    
    
    //////////////////////////////////////////
    // functions
    void PrintErrorMessage(int code);
    void PrintLogMessage(int code, std::string insert);
    void addLogMessageType(std::string &message, int code);
    
    void setFileName(std::string in);
    //////////////////////////////////////////
    // de- & constructors
    ConstStrings();
    ConstStrings(const ConstStrings& orig);
    virtual ~ConstStrings();
    //////////////////////////////////////////
    
    
    //////////////////////////////////////////
    // global variables

    // flags
    bool flag_ital;
    bool flag_table_mode;

    bool error_appeared;
    
    // path to opened file
    std::string opened_file;

    // pdf-viewer id
    pid_t pdf_viewer_pid;
    
    // keep files - flags
    bool keep_some_files_gtk;
    bool keep_tex_file;
    bool keep_log_file;
    bool keep_aux_file;
    
    // document class
    int document_mode; // 1: article, 2: beamer 3: report
    
    
    // data for modifying tex-file
    std::string document_title;
    std::string document_author;
    
    // to count the tables, columns and rows
    // usage: vector[row][columns]
    std::vector<int> active_table;
    tableoftables vector_of_tables;
    // active_table-1
    int table_counter;
    
    // log buffer of logmessage
    GtkTextBuffer *log_buffer;
    
    // gtk log adjustment of scrolledwindow_log
    GtkAdjustment *log_adj;
    
    // tex conversion modes
    bool mode_todo;
    int todo_open_line;
    int todo_deep;
    
    bool mode_fat;
    int fat_open_line;
    bool mode_ital;
    int ital_open_line;
    bool mode_center;
    int center_open_line;
    bool mode_frame;
    int frame_open_line;
};

#endif	/* CONSTSTRINGS_H */

