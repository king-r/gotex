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
    static void insertNewSection(GtkSourceBuffer *buffer);
    static void insertNewSubsection(GtkSourceBuffer *buffer);
    static void insertNewImage(GtkSourceBuffer *buffer);
    static void insertNewTable(GtkSourceBuffer *buffer);
    static void insertItemization(GtkSourceBuffer *buffer);
    static void surroundTextSelection(GtkSourceBuffer *buffer, std::string text_left, std::string text_right);
    
    BufferModificator();
    BufferModificator(const BufferModificator& orig);
    virtual ~BufferModificator();
private:
    // helpers
    static void getIterAtCursor(GtkTextIter &iter, GtkSourceBuffer *buffer);

};

#endif	/* BUFFERMODIFICATOR_H */

