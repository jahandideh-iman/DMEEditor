#include "DecisionTreeIOManager.h"
#include "DecisionTreeEditor.h"
#include "DecisionNode.h"
#include "ActionNode.h"
#include "QFile"

DecisionTreeIOManager::DecisionTreeIOManager(DecisionTreeEditor *editor)
{
    this->editor = editor;
}

DecisionTreeIOManager::~DecisionTreeIOManager()
{

}

void DecisionTreeIOManager::ReadFrom(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray dataArray = file.readAll();
        //QString data = file.readAll().toStdString();
        xml_document<> xmlData;
        xmlData.parse<0>(dataArray.data());
        xml_node<char>* rootXMLNode = xmlData.first_node("DMEComponent");
        if(rootXMLNode != nullptr )
        {
            editor->SetRoot(ExtractNode(rootXMLNode->first_node("Node")));
        }

    }
    file.close();
}

DecisionTreeNode *DecisionTreeIOManager::ExtractNode(DecisionTreeIOManager::XMLNode *xmlNode, DecisionTreeNode *parent)
{
    if (xmlNode == nullptr)
        return nullptr;

    QString nodeType = GetNodeType(xmlNode);

    if (nodeType == "ActionNode")
        return ExtractActionNode(xmlNode, parent);
    else if (nodeType == "DecisionNode")
        return ExtractDecisionNode(xmlNode, parent);

    return nullptr;
}

QString DecisionTreeIOManager::GetNodeType(DecisionTreeIOManager::XMLNode *xmlNode)
{
   return xmlNode->first_attribute("type")->value();
}

DecisionTreeNode *DecisionTreeIOManager::ExtractActionNode(DecisionTreeIOManager::XMLNode *xmlNode, DecisionTreeNode *parent)
{
    auto actionNode = new ActionNode(parent);
    XMLNode* actionXMLNode = xmlNode->first_node("Action");
    if (actionXMLNode != nullptr)
        actionNode->SetActionName(actionXMLNode->value());

    ParseNodePosition(actionNode, xmlNode);
    return actionNode;

}

DecisionTreeNode *DecisionTreeIOManager::ExtractDecisionNode(DecisionTreeIOManager::XMLNode *xmlNode, DecisionTreeNode *parent)
{
    auto decisionNode = new DecisionNode(parent);

    ParseNodePosition(decisionNode, xmlNode);
    ParseDecisionNodeCondition(decisionNode, xmlNode);
    ParseDecisionNodeTruePathNode(decisionNode, xmlNode);
    ParseDecisionNodeFalsePathNode(decisionNode, xmlNode);

    return decisionNode;
}

void DecisionTreeIOManager::ParseNodePosition(DecisionTreeNode *node, DecisionTreeIOManager::XMLNode *xmlNode)
{
    float xPos = QString(xmlNode->first_attribute("XPos")->value()).toFloat();
    float yPos = QString(xmlNode->first_attribute("YPos")->value()).toFloat();
    node->setPos(xPos,yPos);

}

void DecisionTreeIOManager::ParseDecisionNodeFalsePathNode(DecisionNode *decisionNode, DecisionTreeIOManager::XMLNode *xmlNode)
{
    XMLNode* falsePathNode = xmlNode->first_node("FalsePath");
    if (falsePathNode != nullptr)
        decisionNode->SetLeftChild(ExtractNode(falsePathNode->first_node("Node"), decisionNode));
}

void DecisionTreeIOManager::ParseDecisionNodeTruePathNode(DecisionNode *decisionNode, DecisionTreeIOManager::XMLNode *xmlNode)
{
    XMLNode* truePathNode = xmlNode->first_node("TruePath");
    if (truePathNode != nullptr)
        decisionNode->SetRightChild(ExtractNode(truePathNode->first_node("Node"),decisionNode));
}

void DecisionTreeIOManager::ParseDecisionNodeCondition(DecisionNode *decisionNode, DecisionTreeIOManager::XMLNode *xmlNode)
{
    XMLNode* conditionXMLNode = xmlNode->first_node("Condition");
    if (conditionXMLNode != nullptr)
        decisionNode->SetConditionName(conditionXMLNode->value());
}

