#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "QString"
#include <Utilities/rapidxml.hpp>

class Editor;
class QFile;

using namespace rapidxml;

class IOManager
{
protected:
    typedef  xml_node<char> XMLNode;

public:
    IOManager();
    ~IOManager();

    static QString ReadFileType(QString &fileName);

    void SaveToFile(QString &fileName, Editor *editor);
    void ReadFromFile(QString &fileName, Editor *editor);

    virtual bool IsCompatibleWith(Editor *editor) = 0;

    bool IsFileTypeValid(QString fileType);

protected:
    virtual void Parse(XMLNode *rootXMLNode, Editor *editor) = 0;
    virtual void Save(Editor *editor) = 0;
    virtual QString GetType() = 0;

    void WriteToFile(QString text);

private:
    static XMLNode * GetRootXMLNode(QByteArray &dataArray);
    static QByteArray ReadFileData(QString &fileName);

    QFile* file = nullptr;
};

#endif // IOMANAGER_H
