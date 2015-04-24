#ifndef DECISIONTREEIOMANAGER_H
#define DECISIONTREEIOMANAGER_H

#include <QVector>
#include <rapidxml.hpp>

#include <QMap>

using namespace rapidxml;

class StateNode;
class DecisionTreeEditor;
class DecisionTreeNode;
class DecisionNode;
class QFile;

class DecisionTreeIOManager
{
    typedef  xml_node<char> XMLNode;
public:
    DecisionTreeIOManager(DecisionTreeEditor *editor);
    ~DecisionTreeIOManager();

    void ReadFrom(QString &fileName);

private:
    DecisionTreeNode *ExtractNode(XMLNode* xmlNode, DecisionTreeNode *parent = 0);
    QString GetNodeType(XMLNode* xmlNode);

    DecisionTreeNode *ExtractActionNode(XMLNode *xmlNode, DecisionTreeNode *parent);
    DecisionTreeNode *ExtractDecisionNode(XMLNode *xmlNode, DecisionTreeNode *parent);

    void ParseNodePosition(DecisionTreeNode *node, XMLNode *xmlNode);

    void ParseDecisionNodeFalsePathNode(DecisionNode* decisionNode, XMLNode* xmlNode);
    void ParseDecisionNodeTruePathNode(DecisionNode* decisionNode,  XMLNode* xmlNode);
    void ParseDecisionNodeCondition(DecisionNode* decisionNode, XMLNode* xmlNode);

private:
    DecisionTreeEditor *editor = nullptr;
};

#endif // DECISIONTREEIOMANAGER_H
