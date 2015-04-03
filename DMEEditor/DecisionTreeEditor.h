#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "UndeterminedDecisionTreeNode.h"
#include "ActionNode.h"
#include "DecisionNode.h"

class DecisionTreeEditor
{
public:
    DecisionTreeEditor();
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

    DecisionTreeNode* root;
};

#endif // DECISIONTREEEDITOR_H
