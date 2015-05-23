/* 
 * File:   FileOperator.h
 * Author: roli
 *
 * Created on 31. März 2015, 17:31
 */


#ifndef FILEOPERATOR_H
#define	FILEOPERATOR_H

class FileOperator {
public:
    // functions
    static void newFile(GtkSourceBuffer *buffer);
    static void saveFileAs(GtkSourceView *textview, ConstStrings *error);
    static void checkSaveFile(GtkSourceView *textview, ConstStrings *error);
    static void saveFile(GtkSourceView *textview, std::string filename);
    static void openFile(GtkSourceBuffer *buffer);
    static void createTexFile(GtkSourceView *textview, ConstStrings *error);
    static void goTex(GtkSourceView *textview, GtkSourceBuffer *buffer, ConstStrings *error);
    static void clearLog(GtkTextBuffer *log_buffer, ConstStrings *error);
    
    // con- & destructor
    FileOperator();
    FileOperator(const FileOperator& orig);
    virtual ~FileOperator();
private:
    // gotex helpers
    static std::string deleteGeneratedFiles(std::string filename, ConstStrings *error);
    static std::string deleteGeneratedBeamerFiles(std::string filename, ConstStrings *error);

};

#endif	/* FILEOPERATOR_H */

