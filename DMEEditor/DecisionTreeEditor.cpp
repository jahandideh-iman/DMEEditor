#include "DecisionTreeEditor.h"

DecisionTreeEditor::DecisionTreeEditor(PropertyPanel* propertyPanel)
{
    this->propertyPanel = propertyPanel;

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    root = new UndeterminedDecisionTreeNode(this,nullptr, propertyPanel);
    scene->addItem(root);
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

DecisionTreeNode *DecisionTreeEditor::CreateActionNodeFrom(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionTreeNode* newNode = new ActionNode(propertyPanel);
    scene->addItem(newNode);
    newNode->setPos(undeterminedNode->pos());

    return newNode;
}

DecisionTreeNode *DecisionTreeEditor::CreateDecisionNodeFrom(UndeterminedDecisionTreeNode *undeterminedNode)
{
    DecisionNode* newNode = new DecisionNode(propertyPanel);
    DecisionTreeNode* rightChild = new UndeterminedDecisionTreeNode(this, newNode, propertyPanel);
    DecisionTreeNode* leftChild = new UndeterminedDecisionTreeNode(this, newNode, propertyPanel);

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

