#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "UndeterminedDecisionTreeNode.h"
#include "ActionNode.h"
#include "DecisionNode.h"

class PropertyPanel;
class QFile;

class DecisionTreeEditor
{
public:
    DecisionTreeEditor(PropertyPanel* propertyPanel);
    ~DecisionTreeEditor();


    QGraphicsView *GetView() const;

    void ConvertToActionNode(UndeterminedDecisionTreeNode* undeterminedNode);
    void ConvertToDecisionNode(UndeterminedDecisionTreeNode* undeterminedNode);

    void SaveToFile(QString &fileName);

private:
    DecisionTreeNode* CreateActionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);
    DecisionTreeNode* CreateDecisionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);

    void ReplaceAndDeleteUndeterminedNode(UndeterminedDecisionTreeNode *undeterminedNode, DecisionTreeNode *newNode);

    void SaveNode(DecisionTreeNode* node, QFile* file, int depth = 1);
private:
    QGraphicsScene *scene = nullptr;
    QGraphicsView *view = nullptr;

    PropertyPanel* propertyPanel = nullptr;

    DecisionTreeNode* root = nullptr;
};

#endif // DECISIONTREEEDITOR_H
