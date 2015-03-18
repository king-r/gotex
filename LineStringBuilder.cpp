/* 
 * File:   LineStringBuilder.cpp
 * Author: roli
 * 
 * Created on 1. Februar 2015, 22:41
 */

#include <iostream> // remove! TODO

#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "LineStringBuilder.h"

#include "ConstStrings.h"


////////////////////////////////
// Stringhandler
////////////////////////////////
// handles line from textfile 
// return-val: line from file
// includes the following commands:
// - #img
// - #titlepage
//
// - #todo todo#
// - #fat fat#
// - #ital ital#
// - #newpage
// - #center center#
// - #frame frame#
// - #newline
// - #pause
//
// noncombinable commands
// - #table
// - #title
// - #subtitle
// - #section
// - #subsection
// - - (itemization)
// - #doctitle
// - #author
//
// character replacements
// - ...
// - #
// - &
// - <
// - >
std::string LineStringBuilder::handleString(std::string in, std::ofstream &output ,int &list_deep, ConstStrings *error)
{
    size_t found_pos = 0;
    bool stop_itemization = true;
    bool exit = false;

    ////////////////////////////////
    // simple replacements
    //
    checkForSimpleReplacements(in);

    ////////////////////////////////
    // table specific algorithms
    //
    // check if table mode is on
    exit = checkForTableMode(in, output, error);
    if (exit == true)
    {
        return in;
    }
    // if "#pause" was found, replace with "\pause" 
    if((found_pos = in.find(ConstStrings::marker_pause)) != std::string::npos)
    {
        std::string begin = gereateTabulatorDeep(list_deep/2 + 1);
        if(list_deep/2 + 1 == 1)
        {
            begin = error->string_tabulator;
        }
        replaceIfFound(in, ConstStrings::marker_pause, begin + ConstStrings::string_pause);
        stop_itemization = false;
    }

    ////////////////////////////////
    // image specific algorithm
    if( (found_pos = in.find(ConstStrings::marker_img)) != std::string::npos )
    {
        checkImage(in, found_pos, output, error);
    }
    
    ////////////////////////////////
    // non-combinable command algorithms
    
    // not working yet:
    exit = checkForNonCombinableCommands(in, output, list_deep, stop_itemization, error);    
    
    return in;
}


////////////////////////////////
// corrects generated tex-file
// inserts saved data from text-file
std::string LineStringBuilder::correctTexString(std::string in, ConstStrings* error)
{    
    size_t found_pos = 0;
    
    // set document title
    if( (found_pos = in.find(ConstStrings::marker_base_doctitle) ) != std::string::npos)
    {
        in.erase(found_pos, ConstStrings::marker_base_doctitle.size());
        in.insert(found_pos, error->document_title);
    }
    
    // set document author
    if( (found_pos = in.find(ConstStrings::marker_base_author)) != std::string::npos)
    {
        in.erase(found_pos, ConstStrings::marker_base_author.size());
        in.insert(found_pos, error->document_author);
    }
    
    return in;
}



////////////////////////////////
// String handler algorithms
////////////////////////////////

////////////////////////////////
// checks if table mode is on
// writes "\hline"s and 
// return: exit mode
bool LineStringBuilder::checkForTableMode(std::string &in, std::ofstream& output, ConstStrings *error)
{
    size_t found_pos = 0;
    if(error->flag_table_mode == true)
    {
        // write hline
        writeToFile(error->string_tabulator + error->string_hline, output);
        if((found_pos = in.find(error->marker_table_end)) != std::string::npos)
        {
            in = checkEndTable(in, output, error);
        }
        else
        {
            while((found_pos = in.find(error->marker_table_column)) != std::string::npos)
            {
                in = replaceIfFound(in, ConstStrings::marker_table_column, ConstStrings::marker_and + " ");
            }
            
            // count the columns of the row 
           int i = 2;
            for(found_pos = 0; std::string::npos != (found_pos = in.find(error->string_and, found_pos+1) ); i++)
            {
                size_t found_backslash = found_pos;
                if(in.find("\\", found_backslash) == found_backslash)
                {
                    i--;
                }
            }
            std::cout << i << std::endl;
            //error->vector_of_tables[error->table_counter].push_back(i);
            in = error->string_tabulator + in + " " + error->string_newline;
        }
        
        
        
        // characters usable in tables
        replaceIfFoundWithoutCharacter(in, ConstStrings::marker_hashtag, ConstStrings::string_hashtag, '\\');

        writeToFile(in, output);
        if(error->flag_table_mode == false)
        {
            writeToFile(ConstStrings::string_center_end, output);
        }
        return true;
    }
    return false;
}

////////////////////////////////
// checks line from file for simple replacement commands
// it contains the following commands:
// - #todo todo#
// - #fat fat#
// - #ital ital#
// - #newpage
// - #center center#
// - #frame frame#
// - #newline
void LineStringBuilder::checkForSimpleReplacements(std::string& in)
{
    // if "#titlepage" is found, replace with "\maketitle"
    replaceIfFound(in, ConstStrings::marker_titlepage, ConstStrings::string_titlepage);
    // if "#todo" is found replace with "\\todo{"
    replaceIfFound(in, ConstStrings::marker_todo, ConstStrings::string_todo);
    // if "todo#" is found replace with "}"
    replaceIfFound(in, ConstStrings::marker_todo_end, ConstStrings::string_close_bracket);
    // if "#fat" was found replace with "\\textbf{"
    replaceIfFound(in, ConstStrings::marker_fat, ConstStrings::string_begin_textbf);
    // if "fat#" was found replace with "}"
    replaceIfFound(in, ConstStrings::marker_fat_end, ConstStrings::string_close_bracket, -1);
    // if "ital#" was found replace with "}"
    replaceIfFound(in, ConstStrings::marker_ital_end, ConstStrings::string_close_bracket, -1);
    // if "#ital" was found replace with"\begin{textit}
    replaceIfFound(in, ConstStrings::marker_ital, ConstStrings::string_begin_textit);
    // if "#newpage" was found replace with "\newpage"
    replaceIfFound(in, ConstStrings::marker_newpage, ConstStrings::string_newpage);
    // if "#center" was found replace with "\begin{center}"
    replaceIfFound(in, ConstStrings::marker_center, ConstStrings::string_center);
    // if "center#" was found replace with "\end{center}"
    replaceIfFound(in, ConstStrings::marker_center_end, ConstStrings::string_center_end, -1);
    // if "#frame" was found, replace with "\begin{frame}"
    replaceIfFound(in, ConstStrings::marker_frame, ConstStrings::string_frame);
    // if "frame#" was found, replace with "\end{frame}"
    replaceIfFound(in, ConstStrings::marker_frame_end, ConstStrings::string_frame_end);
    // if "#newline" was found, replace with "\\"
    replaceIfFound(in, ConstStrings::marker_newline, ConstStrings::string_newline);        
    
    return;
}

////////////////////////////////
// noncombinable commands
// it contains the folloing commands:
// - #table
// - #title
// - #subtitle
// - #section
// - #subsection
// - - (itemization)
// - #doctitle
// - #author
bool LineStringBuilder::checkForNonCombinableCommands(std::string& in, std::ofstream& output, int &list_deep, bool stop_itemization, ConstStrings* error)
{
    size_t found_pos = 0;
    // if #table is found, checkTable
    if( (found_pos = in.find(ConstStrings::marker_table)) != std::string::npos)
    {
        writeToFile(ConstStrings::string_center, output);
        checkTable(in, output, error);
        writeToFile(in, output);
        error->flag_table_mode = true;
        
        error->table_counter++;
        std::cout << error->table_counter << std::endl;
    }
    // if "#title" is found
    else if( (found_pos = in.find(ConstStrings::marker_title)) != std::string::npos)
    {
        replaceIfFound(in, ConstStrings::marker_title, ConstStrings::string_title);
        in += ConstStrings::string_close_bracket;
        writeToFile(in, output);
    }
    // if "#subtitle" is found
    else if( (found_pos = in.find(ConstStrings::marker_subtitle)) != std::string::npos)
    {
        replaceIfFound(in, ConstStrings::marker_subtitle, ConstStrings::string_subtitle);
        in += ConstStrings::string_close_bracket;
        writeToFile(in, output);
    }
    // if "#section" is found 
    else if( (found_pos = in.find(ConstStrings::marker_section)) != std::string::npos)
    {
        if('*' == in.at(ConstStrings::marker_section.size()))
        {
            replaceIfFound(in, ConstStrings::marker_section, ConstStrings::string_section_star);
        }
        else
        {
            replaceIfFound(in, ConstStrings::marker_section, ConstStrings::string_section);
        }
        in += ConstStrings::string_close_bracket;
        writeToFile(in, output);        
    }
    // if "#subsection" is found
    else if( (found_pos = in.find(ConstStrings::marker_subsection)) != std::string::npos)
    {
        if('*' == in.at(ConstStrings::marker_subsection.size()))
        {
            replaceIfFound(in, ConstStrings::marker_subsection, ConstStrings::string_subsection_star);
        }
        else
        {
            replaceIfFound(in, ConstStrings::marker_subsection, ConstStrings::string_subsection);
        }
        in += ConstStrings::string_close_bracket;
        writeToFile(in, output);
    }
    // if "-" was found check for itemization
    else if( ( (found_pos = in.find(ConstStrings::marker_listentry) ) != std::string::npos)
     &&  ((found_pos == 0) || (in.at(found_pos-1) == ' ')) && (stop_itemization == true) )
    {
        checkForSimpleCharacterReplacements(in);
        checkItemization(in, list_deep, output, error);
    }
    // if "#doctitle" is found
    else if( (found_pos = in.find(ConstStrings::marker_doctitle)) != std::string::npos )
    {
        in.erase(found_pos, ConstStrings::marker_doctitle.size()+1);
        error->document_title = in;
        return true; //exit handlestring()
    }
    // if "#author" is found
    else if( (found_pos = in.find(ConstStrings::marker_author)) != std::string::npos)
    {
        in.erase(found_pos, ConstStrings::marker_author.size()+1);
        error->document_author = in;
        return true; //exit handlestring()
    }
    else
    {
        // characters which are enclosed in gotex commands
        checkForSimpleCharacterReplacements(in);
        
        //write missings \end{itemize}
        if(stop_itemization == true)
        {
            std::string begin = "";
            for(int x = list_deep; x != 0; x--)
            {
                begin = gereateTabulatorDeep(x);
                writeToFile(begin + ConstStrings::string_end_itemize, output);
            }
            list_deep = 0;
        }
        writeToFile(in, output);
    }
    return false;
}


////////////////////////////////
// checks line from file for simple character replacements
// it contains the following character replacements:
// - ...
// - #
// - &
// - >
// - <
void LineStringBuilder::checkForSimpleCharacterReplacements(std::string& in) 
{
    // if "..." is found replace with " \\ldots"
    replaceIfFound(in, ConstStrings::marker_ldots, " " + ConstStrings::string_ldots + " ");
    // if "#" was found replace with '\#'
    replaceIfFoundWithoutCharacter(in, ConstStrings::marker_hashtag, ConstStrings::string_hashtag, '\\');
    // if "&" was found replace with "\&"
    replaceIfFoundWithoutCharacter(in, ConstStrings::marker_and, ConstStrings::string_and, '\\');
    // if ">" was found replace with "$>$"
    replaceIfFoundWithoutCharacter(in, ConstStrings::marker_bigger_than, ConstStrings::string_bigger_than, '$');
    // if "<" was found replace with "$<$"
    replaceIfFoundWithoutCharacter(in, ConstStrings::marker_smaller_than, ConstStrings::string_smaller_than, '$');
    
    return;
}


////////////////////////////////
// gotex command algorithms
////////////////////////////////

////////////////////////////////
// image
std::string LineStringBuilder::checkImage(std::string &in, size_t found_pos, std::ofstream &output, ConstStrings *error)
{
    //center if not in table mode
    if(error->flag_table_mode == false)
    {
        in.insert(found_pos, ConstStrings::string_center);
    }
    
    //get image path
    std::string path = getPathFromFullPath(error->opened_file); 

    // if "#img medium" is found
    std::string tex_string_sceme = ConstStrings::string_img + path;
    std::string tex_command_img_medium = tex_string_sceme;
    tex_command_img_medium.replace(tex_command_img_medium.find("<width>"), 7, "7");
    replaceIfFound(in, ConstStrings::marker_img_medium, tex_command_img_medium);
    
    // if "#img small" is found
    std::string tex_command_img_small = tex_string_sceme;
    tex_command_img_small.replace(tex_command_img_small.find("<width>"), 7, "4");
    
    replaceIfFound(in, ConstStrings::marker_img_small, tex_command_img_small);
    
    // if "#img big" is found
    std::string tex_command_img_big = tex_string_sceme;
    tex_command_img_big.replace(tex_command_img_big.find("<width>"), 7, "10");
    replaceIfFound(in, ConstStrings::marker_img_big, tex_command_img_big);
    
    // if "#img" is found
    replaceIfFound(in, ConstStrings::marker_img, tex_command_img_medium);
    
    // set close bracket and end center
    found_pos = in.find(" ", found_pos);
    if(error->flag_table_mode == true && found_pos == std::string::npos )
    {
        in.append(ConstStrings::string_close_bracket);
    }
    if(error->flag_table_mode == true && found_pos != std::string::npos )
    {
        in.insert(found_pos, ConstStrings::string_close_bracket);
    }
    if(error->flag_table_mode == false && found_pos != std::string::npos )
    {
        in.insert(found_pos, ConstStrings::string_close_bracket + ConstStrings::string_center_end);
    }
    if(error->flag_table_mode == false && found_pos == std::string::npos)
    {
        in.append(ConstStrings::string_close_bracket + ConstStrings::string_center_end);
    }

    
    return in;
}


////////////////////////////////
// table
std::string LineStringBuilder::checkTable(std::string& in, std::ofstream& output, ConstStrings* error)
{    
    size_t pos_x = 0, found_pos = 0;
    found_pos = in.find(error->marker_table);
    pos_x = in.find(" ", found_pos);

    //read width of 
    char c = '0';
    int i = 1;

    std::string width = "";
    c = '0';
    while((c != ' '))
    {
        if(pos_x + i >= in.size())
            break;
        c = in.at(pos_x + i);
        in.at(pos_x + i) = ' ';
        width = width + c;
        i++;
    }
    int columns = atoi(width.c_str());
    
    std::string columns_tex = "";
    for(; columns > 0;columns--)
    {
        columns_tex = columns_tex + "|c";
    }
    columns_tex = columns_tex + "|";
    
    std::string command_begin = error->string_table + columns_tex + error->string_close_bracket;

    in = replaceIfFound(in, error->marker_table, command_begin, 0);
    return in;
}

std::string LineStringBuilder::checkEndTable(std::string& in, std::ofstream& output, ConstStrings* error)
{
    error->flag_table_mode = false;
    in = replaceIfFound(in, error->marker_table_end, error->string_table_end);
    return in;
}


////////////////////////////////
// itemization 
std::string LineStringBuilder::checkItemization(std::string &in, int &list_deep, std::ofstream &output, ConstStrings *error)
{   
    size_t found_pos = in.find(ConstStrings::marker_listentry);
    int deep = found_pos / 2 + 1;// must be configured for different tabulator
    
    in.erase(found_pos, ConstStrings::marker_listentry.size());
    in.insert(found_pos, ConstStrings::string_item + " ");
        
    std::string begin = "";

    if (list_deep > deep)
    {
        for(int x = list_deep; x != deep; x--)
        {
            begin = gereateTabulatorDeep(list_deep);
            writeToFile(begin + ConstStrings::string_end_itemize, output);
        }
    }
    else if (list_deep <  deep)
    {        
        begin = gereateTabulatorDeep(deep);
        writeToFile(begin + ConstStrings::string_begin_itemize, output);
    }
    in.erase(0, found_pos);
    if (error->flag_ital == true)
    {            
        in.insert(ConstStrings::string_item.size()+1, ConstStrings::string_begin_textit);
        error->flag_ital = false;
    }
    
    begin = gereateTabulatorDeep(deep+1);
    writeToFile(begin + in, output);
        
    list_deep = deep;
        
    return in;
}



////////////////////////////////
// helper functions
////////////////////////////////

////////////////////////////////
// removes filename from path
std::string LineStringBuilder::getPathFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(0, pos+1);
}


////////////////////////////////
// simple replacement function
std::string LineStringBuilder::replaceIfFound(std::string &in, std::string search, std::string insert)
{
    return replaceIfFound(in, search, insert, 0);
}

std::string LineStringBuilder::replaceIfFound(std::string &in, std::string search, std::string insert, int pos_mod)
{
    size_t found_pos = 0;
    // if string was found was found
    while ( ( found_pos = in.find(search)) != std::string::npos)
    {
        in.erase(found_pos + pos_mod, search.size()+1);
        in.insert(found_pos + pos_mod, insert);
    }
    return in;
}

////////////////////////////////
// special replacement function
// replaces only, if character is not found before the search-string
std::string LineStringBuilder::replaceIfFoundWithoutCharacter(std::string& in, std::string search, std::string insert, char c, int pos_mod)
{
    size_t found_pos = 0;
    // if string was found was found
    while ( ( found_pos = in.find(search, found_pos)) != std::string::npos)
    {
        if( (found_pos > 1) && (in.at(found_pos-1) == c) )
        {
            continue;
        }
        in.erase(found_pos + pos_mod, search.size());
        in.insert(found_pos + pos_mod, insert);
        found_pos+=2;
    }
    return in;
}

std::string LineStringBuilder::replaceIfFoundWithoutCharacter(std::string &in, std::string search, std::string insert, char c)
{
    return replaceIfFoundWithoutCharacter(in, search, insert, c, 0);
}

////////////////////////////////
// generates a tabulator string for a certain deep
std::string LineStringBuilder::gereateTabulatorDeep(int deep)
{   
    std::string begin = "";
    for(int x = deep-1; x!= 0; x--)
    {
        begin += ConstStrings::string_tabulator;
    }
    return begin;
}

////////////////////////////////
// writes to file
void LineStringBuilder::writeToFile(std::string text, std::ofstream &file)
{
    file << text << std::endl;
}



////////////////////////////////
// De- & Constructors
////////////////////////////////

LineStringBuilder::LineStringBuilder() {
}

LineStringBuilder::LineStringBuilder(const LineStringBuilder& orig) {
}

LineStringBuilder::~LineStringBuilder() {
}

