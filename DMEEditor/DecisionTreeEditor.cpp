#include "DecisionTreeEditor.h"
#include <QFile>

DecisionTreeEditor::DecisionTreeEditor()
{

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    SetRoot(new UndeterminedDecisionTreeNode(this,nullptr));

    ioManager = new DecisionTreeIOManager(this);

}


DecisionTreeEditor::~DecisionTreeEditor()
{
    delete view;
    delete scene;
    delete root;
}

 QGraphicsView *DecisionTreeEditor::GetView() const
{
     return view;
}

void DecisionTreeEditor::ConvertToActionNode(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionTreeNode* newNode = CreateActionNodeFrom(undeterminedNode);
    ReplaceAndDeleteUndeterminedNode(undeterminedNode, newNode);
}

void DecisionTreeEditor::ConvertToDecisionNode(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionTreeNode* newNode = CreateDecisionNodeFrom(undeterminedNode);
    ReplaceAndDeleteUndeterminedNode(undeterminedNode, newNode);
}

void DecisionTreeEditor::SaveToFile(QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write("<DMEComponent type=\"DecisionTree\" >\n" );
        SaveNode(root, &file);
        file.write("</DMEComponent>\n");
        file.close();
    }
}

void DecisionTreeEditor::OpenFromFile(QString &fileName)
{
    ioManager->ReadFrom(fileName);
}

void DecisionTreeEditor::SetRoot(DecisionTreeNode *node)
{
    root = node;
    scene->addItem(root);
}

DecisionTreeNode *DecisionTreeEditor::CreateActionNodeFrom(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionTreeNode* newNode = new ActionNode();
    scene->addItem(newNode);
    newNode->setPos(undeterminedNode->pos());

    return newNode;
}

DecisionTreeNode *DecisionTreeEditor::CreateDecisionNodeFrom(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionNode* newNode = new DecisionNode();
    DecisionTreeNode* rightChild = new UndeterminedDecisionTreeNode(this, newNode);
    DecisionTreeNode* leftChild = new UndeterminedDecisionTreeNode(this, newNode);

    newNode->SetRightChild(rightChild);
    newNode->SetLeftChild(leftChild);

    newNode->setPos(undeterminedNode->pos());
    rightChild->setPos(newNode->pos()+ QPoint(100,100));
    leftChild->setPos(newNode->pos()+ QPoint(-100,100));

    scene->addItem(rightChild);
    scene->addItem(leftChild);
    scene->addItem(newNode);

    return newNode;
}

void DecisionTreeEditor::ReplaceAndDeleteUndeterminedNode(UndeterminedDecisionTreeNode *undeterminedNode, DecisionTreeNode *newNode)
{
    DecisionNode* parentNode = undeterminedNode->getParentNode();
    if(parentNode != nullptr)
        parentNode->ReplaceChild(undeterminedNode, newNode);
    else // if it is root
        root = newNode;

    scene->removeItem(undeterminedNode);
    delete undeterminedNode;
}

void DecisionTreeEditor::SaveNode(DecisionTreeNode *node, QFile *file, int depth)
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

