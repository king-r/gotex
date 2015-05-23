/* 
 * File:   ProgramConfig.h
 * Author: roli
 *
 * Created on 31. März 2015, 18:32
 */

#ifndef PROGRAMCONFIG_H
#define	PROGRAMCONFIG_H

class ProgramConfig {
public:
    static void setKeepSomeFilesConfig(GtkCheckButton *tex_check, GtkCheckButton *log_check, GtkCheckButton *aux_check, ConstStrings *error);
    static void setKeepTexFileConfig(ConstStrings *error);
    static void setKeepLogFileConfig(ConstStrings *error);
    static void setKeepAuxFileConfig(ConstStrings *error);
    static void setDocumentClassConfig(GtkComboBoxText *sender, GtkTextBuffer *buffer, ConstStrings *error);
    
    ProgramConfig();
    ProgramConfig(const ProgramConfig& orig);
    virtual ~ProgramConfig();
private:

};

#endif	/* PROGRAMCONFIG_H */

