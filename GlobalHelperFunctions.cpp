/* 
 * File:   GlobalHelperFunctions.cpp
 * Author: roli
 * 
 * Created on 31. März 2015, 17:58
 */

#include <string>

#include "GlobalHelperFunctions.h"


std::string GlobalHelperFunctions::getPathFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(0, pos);
}

std::string GlobalHelperFunctions::getFilenameFromFullPath(std::string full_path)
{
    unsigned pos = full_path.find_last_of("/");
    return full_path.substr(pos+1);
}

GlobalHelperFunctions::GlobalHelperFunctions() {
}

GlobalHelperFunctions::GlobalHelperFunctions(const GlobalHelperFunctions& orig) {
}

GlobalHelperFunctions::~GlobalHelperFunctions() {
}

