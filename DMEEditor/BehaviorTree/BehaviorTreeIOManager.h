#ifndef BEHAVIORTREEIOMANAGER_H
#define BEHAVIORTREEIOMANAGER_H

#include "Core/IOManager.h"

class BehaviorTreeEditor;
class BehaviorTask;

class BehaviorTreeIOManager : public IOManager
{
public:
    BehaviorTreeIOManager();
    ~BehaviorTreeIOManager();

    bool IsCompatibleWith(Editor *editor) override;

protected:
    void Parse(XMLNode *rootXMLNode, Editor *editor);
    void Save(Editor *editor) ;
    QString GetType();

    BehaviorTreeEditor *editor = nullptr;

private:
    BehaviorTask *ExtractTask(XMLNode* xmlNode, BehaviorTask *parent = 0);
    BehaviorTask *ExtractActionTask(XMLNode *xmlNode, BehaviorTask *parent);
    BehaviorTask *ExtractCompoundTask(XMLNode *xmlNode, BehaviorTask *parent);

    QString GetTaskType(XMLNode* xmlNode);

    void ParseTaskPosition(BehaviorTask *task, XMLNode *xmlNode);

private:
    void SaveTask(BehaviorTask *task, int depth = 1);



};

#endif // BEHAVIORTREEIOMANAGER_H
