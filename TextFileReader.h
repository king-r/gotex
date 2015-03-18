/* 
 * File:   TextFileReader.h
 * Author: roli
 *
 * Created on 31. Januar 2015, 00:47
 */

#ifndef TEXTFILEREADER_H
#define	TEXTFILEREADER_H

#include "ConstStrings.h"

class TextFileReader {
public:
    //////////////////////////////////////////
    // functions
    //////////////////////////////////////////
    void ReadBaseFile(std::ofstream &output, const char *note, ConstStrings* error);
    void ReadNotesFile(std::ofstream &output, const char *notes_filename, ConstStrings* error);
    void CorrectTexFile(ConstStrings *error);
    //////////////////////////////////////////
    // helper functions
    //////////////////////////////////////////
    std::string getPathFromFullPath(std::string full_path);
    void writeDocumentMode(std::string &file_line, ConstStrings *error);
    void writeToFile(std::string text, std::ofstream &file);
    //////////////////////////////////////////
    // de- & constructors
    //////////////////////////////////////////    
    TextFileReader();
    TextFileReader(const TextFileReader& orig);
    virtual ~TextFileReader();
private:
    //////////////////////////////////////////
    // attributes
    //////////////////////////////////////////   
    int list_deep;

};

#endif	/* TEXTFILEREADER_H */

