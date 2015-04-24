#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "QString"
class Editor;

class IOManager
{
public:
    IOManager();
    ~IOManager();

    virtual void SaveToFile(QString &fileName, Editor *editor) = 0;
    virtual void ReadFromFile(QString &fileName, Editor *editor) = 0;

    virtual bool IsCompatibleWith(Editor *editor) = 0;
    virtual bool IsFileValid(QString &fileName) = 0;
};

#endif // IOMANAGER_H
