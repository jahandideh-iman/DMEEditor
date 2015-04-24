#include "DecisionTreeEditor.h"
#include <QFile>

DecisionTreeEditor::DecisionTreeEditor()
{

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    SetRoot(new UndeterminedDecisionTreeNode(this,nullptr));

    ioManager = new DecisionTreeIOManager();

}


DecisionTreeEditor::~DecisionTreeEditor()
{

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


void DecisionTreeEditor::SetRoot(DecisionTreeNode *node)
{
    root = node;
    scene->addItem(root);
}

DecisionTreeNode *DecisionTreeEditor::GetRoot()
{
    return root;
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



