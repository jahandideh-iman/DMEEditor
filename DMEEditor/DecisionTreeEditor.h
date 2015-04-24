#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "UndeterminedDecisionTreeNode.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include "DecisionTreeIOManager.h"
#include "Editor.h"

class PropertyPanel;
class QFile;

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

    DecisionTreeIOManager *ioManager = nullptr;
};

#endif // DECISIONTREEEDITOR_H
