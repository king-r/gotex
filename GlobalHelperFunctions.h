/* 
 * File:   GlobalHelperFunctions.h
 * Author: roli
 *
 * Created on 31. März 2015, 17:58
 */

#ifndef GLOBALHELPERFUNCTIONS_H
#define	GLOBALHELPERFUNCTIONS_H

class GlobalHelperFunctions {
public:
    static std::string getPathFromFullPath(std::string full_path);
    static std::string getFilenameFromFullPath(std::string full_path);
    
    GlobalHelperFunctions();
    GlobalHelperFunctions(const GlobalHelperFunctions& orig);
    virtual ~GlobalHelperFunctions();
private:

};

#endif	/* GLOBALHELPERFUNCTIONS_H */

