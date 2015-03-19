/* 
 * File:   LineStringBuilder.h
 * Author: roli
 *
 * Created on 1. Februar 2015, 22:41
 */

#ifndef LINESTRINGBUILDER_H
#define	LINESTRINGBUILDER_H

#include "ConstStrings.h"

class LineStringBuilder {
public:
    
    //////////////////////////////////////////
    // functions
    //////////////////////////////////////////
    // replacement function, command -> tex
    std::string handleString(std::string in, std::ofstream &output ,int &list_deep, ConstStrings *error);
    // replacement function, correction of generated tex file
    std::string correctTexString(std::string in, ConstStrings *error);
    std::string generateColumnsFromInt(int columns_quantity);
    // string handler algorithms
    bool checkForTableMode(std::string &in, std::ofstream &output, ConstStrings *error);
    void checkForSimpleReplacements(std::string &in);
    void checkForSimpleCharacterReplacements(std::string &in);
    bool checkForNonCombinableCommands(std::string &in, std::ofstream &output, int &list_deep, bool stop_itemization, ConstStrings *error);
    // gotex command algorithms
    std::string checkItemization(std::string &in, int &list_deep, std::ofstream &output, ConstStrings *error);
    std::string checkImage(std::string &in, size_t found_pos, std::ofstream &output, ConstStrings* error);
    std::string checkTable(std::string &in, std::ofstream &output, ConstStrings *error);
    std::string checkEndTable(std::string &in, std::ofstream &output, ConstStrings *error);
    // helper functions
    std::string getPathFromFullPath(std::string full_path);
    std::string replaceIfFoundWithoutCharacter(std::string &in, std::string search, std::string insert, char c, int pos_mod);
    std::string replaceIfFoundWithoutCharacter(std::string &in, std::string search, std::string insert, char c);
    std::string replaceIfFound(std::string &in, std::string search, std::string insert);
    std::string replaceIfFound(std::string &in, std::string search, std::string insert, int pos_mov);
    std::string gereateTabulatorDeep(int deep);
    void writeToFile(std::string text, std::ofstream &file);
    // de- & constructors
    LineStringBuilder();
    LineStringBuilder(const LineStringBuilder& orig);
    virtual ~LineStringBuilder();
private:

};

#endif	/* LINESTRINGBUILDER_H */

