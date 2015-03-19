/* 
 * File:   TextFileReader.cpp
 * Author: roli
 * 
 * Created on 31. Januar 2015, 00:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ios>
#include <iostream>

#include "TextFileReader.h"

#include "ConstStrings.h"
#include "LineStringBuilder.h"


using std::ifstream;
using std::string;


////////////////////////////////
// file-reader / -writer functions
////////////////////////////////

///////////////////
// Reads Base File and writes the output .tex file
void TextFileReader::ReadBaseFile(std::ofstream &output, const char *notes_filename, ConstStrings *error) {
    // open basefile
    ifstream base_file;
    base_file.open(error->base_filename.c_str());
    if(base_file.fail())
    {
        // Printing Error Message: "Error opening basefile.\n";
        error->PrintErrorMessage(1);
    }
    
    // read file linewise
    string file_line;
    
    // reading base file linewise 
    while(getline(base_file, file_line))
    {
        if(!(base_file.fail()))
        {
            if(file_line.find(error->marker_documentclass) != std::string::npos)
            {
                this->writeDocumentMode(file_line, error);
            }

            if (file_line == ConstStrings::marker_content)
            {
                this->ReadNotesFile(output, notes_filename, error);
            }
            else
            {
                output << file_line << std::endl;
            }
        }
    }
    base_file.close();
    
    CorrectTexFile(error);
}

///////////////////
// reads notes file and calls handle string 
void TextFileReader::ReadNotesFile(std::ofstream &output, const char *notes_filename,  ConstStrings *error)
{
    // opening notes-file
    std::ifstream notes_file;
    
    notes_file.open(notes_filename);
    if(notes_file == NULL)
    {
        //Prints "Error opening Notes-file."    EC 2
        error->PrintErrorMessage(2);
    }
        
    // reading notes-file line by line
    std::string file_line;
    LineStringBuilder *worker = new LineStringBuilder();
    while (getline(notes_file , file_line))
    {
        // processing read line
        std::string processed_line = worker->handleString(file_line, output, list_deep, error);
    }
    
    //write missings \end{itemize}
    for(int x = list_deep; x != 0; x--)
    {
        std::string begin = "";
        for (int y = x-1; y != 0; y--)
        {
            begin += ConstStrings::string_tabulator;
        }
        writeToFile(begin + ConstStrings::string_end_itemize, output);
    }
    list_deep = 0;
}



///////////////////
// inserts missing data and creates final tex file
void TextFileReader::CorrectTexFile(ConstStrings *error)
{
    // reset table_counter
    error->table_counter = 0;
    
    // get filename
    std::string filename = error->opened_file;
    
    // open temp tex file
    filename = getPathFromFullPath(filename);
    filename.append("/tempfile");
    std::ifstream tempfile;
    tempfile.open(filename.c_str(), std::ifstream::in);

    filename = error->opened_file;
    filename.replace(filename.find(error->file_text_ending), 4, error->file_tex_ending);
    std::ofstream texfile;
    texfile.open(filename.c_str(), std::ofstream::out);
    
    // create worker
    LineStringBuilder *worker = new LineStringBuilder();
    
    // read file again linewise
    std::string line_from_file = "";
    while(getline(tempfile, line_from_file))
    {
        if(!(tempfile.fail()))
        {
            // correct Line
            line_from_file = worker->correctTexString(line_from_file, error);
            writeToFile(line_from_file, texfile);
        }
    }
    
    delete worker;

    // close tex file
    texfile.close();
    
    // reset table counter
    error->table_counter = 0;
}




////////////////////////////////
// helper functions
////////////////////////////////

///////////////////
// returns path without the last '/'
std::string TextFileReader::getPathFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(0, pos);
}

///////////////////
// writes to file
void TextFileReader::writeToFile(std::string text, std::ofstream &file)
{
    file << text << std::endl;
}

///////////////////
// inserts the article class 
void TextFileReader::writeDocumentMode(std::string &file_line, ConstStrings* error)
{
    size_t found_pos = file_line.find(error->marker_documentclass);
    file_line.erase(found_pos, error->marker_documentclass.size());
    switch(error->document_mode)
    {
        // article
        case 1: file_line.insert(found_pos, error->string_article); break;
        // beamer
        case 2: file_line.insert(found_pos, error->string_beamer); break;
        // report
        case 3: file_line.insert(found_pos, error->string_report); break;
        default: error->PrintErrorMessage(6); break;
    }
}






///////////////////
// De- & Constructors

TextFileReader::TextFileReader() {
    list_deep = 0;
}

TextFileReader::TextFileReader(const TextFileReader& orig) {
}

TextFileReader::~TextFileReader() {
}

