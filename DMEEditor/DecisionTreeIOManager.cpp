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

void DecisionTreeIOManager::ReadFromFile(QString &fileName, Editor *editor_)
{
    editor = dynamic_cast<DecisionTreeEditor*> (editor_);
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

bool DecisionTreeIOManager::IsFileValid(QString &fileName)
{
    QFile file(fileName);
     xml_node<char>* rootXMLNode = nullptr;
     QByteArray dataArray = nullptr;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        dataArray = file.readAll();
        //QString data = file.readAll().toStdString();
        xml_document<> xmlData;
        xmlData.parse<0>(dataArray.data());
        rootXMLNode = xmlData.first_node("DMEComponent");
    }
    file.close();
    if(rootXMLNode != nullptr)
         return QString::compare(rootXMLNode->first_attribute("type")->value(),"DecisionTree") == 0;
    return false;
}


void DecisionTreeIOManager::SaveToFile(QString &fileName, Editor *editor_)
{
    this->editor = dynamic_cast<DecisionTreeEditor*> (editor_);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write("<DMEComponent type=\"DecisionTree\" >\n" );
        SaveNode(this->editor->GetRoot(), &file);
        file.write("</DMEComponent>\n");
        file.close();
    }
}

void DecisionTreeIOManager::SaveNode(DecisionTreeNode *node, QFile *file, int depth)
{
    if(node == nullptr)
        return;
    QString tabs = QString(depth, '\t');

    QString xPos = "XPos=\"" +QString::number(node->pos().x()) + "\" ";
    QString yPos = "YPos=\"" +QString::number(node->pos().y()) + "\" ";

    if(dynamic_cast<DecisionNode*>(node) != nullptr)
    {
        DecisionNode* decisionNode = dynamic_cast<DecisionNode*>(node);
        file->write( (tabs + "<Node type=\"DecisionNode\" " + xPos + yPos +" > \n").toStdString().c_str());

        file->write( (tabs + '\t' + "<Condition>" + decisionNode->GetConditionName() +"</Condition>" + "\n").toStdString().c_str());
        file->write( (tabs + "\t" + "<TruePath>" + "\n").toStdString().c_str());
        SaveNode(decisionNode->GetRightChild(),file, depth+2);
        file->write( (tabs + "\t" + "</TruePath>" + "\n").toStdString().c_str());
        file->write( (tabs + "\t" + "<FalsePath>" + "\n").toStdString().c_str());
        SaveNode(decisionNode->GetLeftChild(),file, depth+2);
        file->write( (tabs + "\t" + "</FalsePath>" + "\n").toStdString().c_str());

        file->write( (tabs + "</Node> \n").toStdString().c_str());
    }
    else if(dynamic_cast<ActionNode*>(node)!= nullptr)
    {
        ActionNode* actionNode = dynamic_cast<ActionNode*>(node);
        file->write( (tabs + "<Node type=\"ActionNode\" " + xPos + yPos + "> \n").toStdString().c_str());
        file->write((tabs + "\t<Action>" + actionNode->GetActionName() + "</Action> \n").toStdString().c_str());
        file->write( (tabs + "</Node> \n").toStdString().c_str());
    }
}

bool DecisionTreeIOManager::IsCompatibleWith(Editor *editor)
{
    return dynamic_cast<DecisionTreeEditor*> (editor) != nullptr ;
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

