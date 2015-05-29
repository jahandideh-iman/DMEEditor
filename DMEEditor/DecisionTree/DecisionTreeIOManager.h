#ifndef DECISIONTREEIOMANAGER_H
#define DECISIONTREEIOMANAGER_H

#include <QVector>
#include <Utilities/rapidxml.hpp>
#include "Core/IOManager.h"
#include <QMap>

using namespace rapidxml;

class StateNode;
class DecisionTreeEditor;
class DecisionTreeNode;
class DecisionNode;
class QFile;

class DecisionTreeIOManager : public IOManager
{
    typedef  xml_node<char> XMLNode;
public:
    DecisionTreeIOManager();
    ~DecisionTreeIOManager();

    bool IsCompatibleWith(Editor *editor) override;

protected:
    void Parse(XMLNode *rootXMLNode, Editor *editor) override;
    void Save(Editor *editor_) override;
    QString GetType() override;

private:
    void SaveNode(DecisionTreeNode* node, int depth = 1);


    DecisionTreeNode *ExtractNode(XMLNode* xmlNode, DecisionTreeNode *parent = 0);
    DecisionTreeNode *ExtractActionNode(XMLNode *xmlNode, DecisionTreeNode *parent);
    DecisionTreeNode *ExtractDecisionNode(XMLNode *xmlNode, DecisionTreeNode *parent);
    QString GetNodeType(XMLNode* xmlNode);

    void ParseNodePosition(DecisionTreeNode *node, XMLNode *xmlNode);
    void ParseDecisionNodeFalsePathNode(DecisionNode* decisionNode, XMLNode* xmlNode);
    void ParseDecisionNodeTruePathNode(DecisionNode* decisionNode,  XMLNode* xmlNode);
    void ParseDecisionNodeCondition(DecisionNode* decisionNode, XMLNode* xmlNode);

private:
    DecisionTreeEditor *editor = nullptr;
};

#endif // DECISIONTREEIOMANAGER_H
