/* 
 * File:   main.cpp
 * Author: roli
 *
 * Created on 25. Januar 2015, 20:04
 */

// c++ libs
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>


#include "TextFileReader.h"
#include "LineStringBuilder.h"
#include "GtkManager.h"

//helpers
using std::string;
//io
using std::cout;
//using std::cin;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;


int main(int argc, char** argv) 
{
    // to gerenate Error Messages
    ConstStrings *error = new ConstStrings();
    
    // gtk start
    GtkManager *manager = new GtkManager();
    manager->start(argc, argv, error);
    delete manager;
    
    std::cout << error->vector_of_tables.at(0).at(0) << std::endl;
    
    delete error;
    
    return 0;
}

