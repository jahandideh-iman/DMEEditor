#include "DecisionTreeIOManager.h"
#include "DecisionTreeEditor.h"
#include "DecisionNode.h"
#include "ActionNode.h"
#include "QFile"

DecisionTreeIOManager::DecisionTreeIOManager()
{
}

DecisionTreeIOManager::~DecisionTreeIOManager()
{

}

void DecisionTreeIOManager::Save(Editor *editor_)
{
    this->editor = dynamic_cast<DecisionTreeEditor*> (editor_);
    SaveNode(this->editor->GetRoot());


}

void DecisionTreeIOManager::SaveNode(DecisionTreeNode *node, int depth)
{
    if(node == nullptr)
        return;
    QString tabs = QString(depth, '\t');

    QString xPos = "XPos=\"" +QString::number(node->pos().x()) + "\" ";
    QString yPos = "YPos=\"" +QString::number(node->pos().y()) + "\" ";

    if(dynamic_cast<DecisionNode*>(node) != nullptr)
    {
        DecisionNode* decisionNode = dynamic_cast<DecisionNode*>(node);
        WriteToFile( tabs + "<Node type=\"DecisionNode\" " + xPos + yPos +" > \n");

        WriteToFile( tabs + '\t' + "<Condition>" + decisionNode->GetConditionName() +"</Condition>" + "\n");
        WriteToFile( tabs + "\t" + "<TruePath>" + "\n");
        SaveNode(decisionNode->GetRightChild(), depth+2);
        WriteToFile( tabs + "\t" + "</TruePath>" + "\n");
        WriteToFile( tabs + "\t" + "<FalsePath>" + "\n");
        SaveNode(decisionNode->GetLeftChild(), depth+2);
        WriteToFile( tabs + "\t" + "</FalsePath>" + "\n");

        WriteToFile( tabs + "</Node> \n");
    }
    else if(dynamic_cast<ActionNode*>(node)!= nullptr)
    {
        ActionNode* actionNode = dynamic_cast<ActionNode*>(node);
        WriteToFile( tabs + "<Node type=\"ActionNode\" " + xPos + yPos + "> \n");
        WriteToFile(tabs + "\t<Action>" + actionNode->GetActionName() + "</Action> \n");
        WriteToFile( tabs + "</Node> \n");
    }
}

void DecisionTreeIOManager::Parse(DecisionTreeIOManager::XMLNode *rootXMLNode, Editor *editor_)
{
    editor = dynamic_cast<DecisionTreeEditor*> (editor_);
    editor->SetRoot(ExtractNode(rootXMLNode->first_node("Node")));
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

bool DecisionTreeIOManager::IsCompatibleWith(Editor *editor)
{
    return dynamic_cast<DecisionTreeEditor*> (editor) != nullptr ;
}

QString DecisionTreeIOManager::GetType()
{
    return "DecisionTree";
}

