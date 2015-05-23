/* 
 * File:   BufferModificator.h
 * Author: roli
 *
 * Created on 31. März 2015, 18:56
 */

#ifndef BUFFERMODIFICATOR_H
#define	BUFFERMODIFICATOR_H

class BufferModificator {
public:
    // functions
    static void insertNewSection(GtkTextBuffer *buffer);
    static void insertNewSubsection(GtkTextBuffer *buffer);
    static void insertNewImage(GtkTextBuffer *buffer);
    static void insertNewTable(GtkTextBuffer *buffer);
    static void insertItemization(GtkTextBuffer *buffer);
    static void surroundTextSelection(GtkTextBuffer *buffer, std::string text_left, std::string text_right);
    
    BufferModificator();
    BufferModificator(const BufferModificator& orig);
    virtual ~BufferModificator();
private:
    // helpers
    static void getIterAtCursor(GtkTextIter &iter, GtkTextBuffer *buffer);

};

#endif	/* BUFFERMODIFICATOR_H */

