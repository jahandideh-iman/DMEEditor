#include "IOManager.h"
#include <QFile>

IOManager::IOManager()
{

}

IOManager::~IOManager()
{

}

QString IOManager::ReadFileType(QString &fileName)
{

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray dataArray = file.readAll();
        file.close();
        XMLNode* rootXMLNode = GetRootXMLNode(dataArray);
        if(rootXMLNode != nullptr)
             return rootXMLNode->first_attribute("type")->value();
    }
    return false;
}

void IOManager::SaveToFile(QString &fileName, Editor *editor)
{
    file = new QFile(fileName);
    if(file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        WriteToFile("<DMEComponent type=\"" + GetType() +"\" >\n" );
        Save(editor);
        WriteToFile("</DMEComponent>\n");
        file->close();
    }
    delete file;
    file = nullptr;
}

void IOManager::ReadFromFile(QString &fileName, Editor *editor)
{
    file = new QFile(fileName);
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray dataArray = file->readAll();
        XMLNode* rootXMLNode = GetRootXMLNode(dataArray);
        if(rootXMLNode != nullptr )
            Parse(rootXMLNode, editor);
        file->close();
    }
    delete file;
    file = nullptr;
}

IOManager::XMLNode *IOManager::GetRootXMLNode(QByteArray &dataArray)
{
    xml_document<> xmlData;
    xmlData.parse<0>(dataArray.data());
    return xmlData.first_node("DMEComponent");
}

bool IOManager::IsFileTypeValid(QString fileType)
{
    return QString::compare(fileType,GetType()) == 0;
}

void IOManager::WriteToFile(QString text)
{
    assert(file != nullptr);
    file->write(text.toStdString().c_str());
}
