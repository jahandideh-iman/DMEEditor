#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include "Editor.h"

class DecisionNode;
class UndeterminedDecisionTreeNode;
class DecisionTreeNode;


class DecisionTreeEditor : public Editor
{
public:
    DecisionTreeEditor();
    ~DecisionTreeEditor();


    QGraphicsView *GetView() const;

    void ConvertToActionNode(UndeterminedDecisionTreeNode* undeterminedNode);
    void ConvertToDecisionNode(UndeterminedDecisionTreeNode* undeterminedNode);

    void SetRoot(DecisionTreeNode *node);
    DecisionTreeNode *GetRoot();

private:
    DecisionTreeNode* CreateActionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);
    DecisionTreeNode* CreateDecisionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);

    void ReplaceAndDeleteUndeterminedNode(UndeterminedDecisionTreeNode *undeterminedNode, DecisionTreeNode *newNode);


private:
    DecisionTreeNode* root = nullptr;

};

#endif // DECISIONTREEEDITOR_H
