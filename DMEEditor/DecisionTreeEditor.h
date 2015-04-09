#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "UndeterminedDecisionTreeNode.h"
#include "ActionNode.h"
#include "DecisionNode.h"

class PropertyPanel;

class DecisionTreeEditor
{
public:
    DecisionTreeEditor(PropertyPanel* propertyPanel);
    ~DecisionTreeEditor();


    QGraphicsView *GetView() const;

    void ConvertToActionNode(UndeterminedDecisionTreeNode* undeterminedNode);
    void ConvertToDecisionNode(UndeterminedDecisionTreeNode* undeterminedNode);

private:
    DecisionTreeNode* CreateActionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);
    DecisionTreeNode* CreateDecisionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);

    void ReplaceAndDeleteUndeterminedNode(UndeterminedDecisionTreeNode *undeterminedNode, DecisionTreeNode *newNode);
private:
    QGraphicsScene *scene = nullptr;
    QGraphicsView *view = nullptr;

    PropertyPanel* propertyPanel = nullptr;

    DecisionTreeNode* root = nullptr;
};

#endif // DECISIONTREEEDITOR_H
