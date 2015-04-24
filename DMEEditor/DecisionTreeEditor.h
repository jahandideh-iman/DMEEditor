#ifndef DECISIONTREEEDITOR_H
#define DECISIONTREEEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "UndeterminedDecisionTreeNode.h"
#include "ActionNode.h"
#include "DecisionNode.h"
#include "DecisionTreeIOManager.h"

class PropertyPanel;
class QFile;

class DecisionTreeEditor
{
public:
    DecisionTreeEditor();
    ~DecisionTreeEditor();


    QGraphicsView *GetView() const;

    void ConvertToActionNode(UndeterminedDecisionTreeNode* undeterminedNode);
    void ConvertToDecisionNode(UndeterminedDecisionTreeNode* undeterminedNode);

    void SaveToFile(QString &fileName);
    void OpenFromFile(QString &fileName);

    void SetRoot(DecisionTreeNode *node);

private:
    DecisionTreeNode* CreateActionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);
    DecisionTreeNode* CreateDecisionNodeFrom(UndeterminedDecisionTreeNode* undeterminedNode);

    void ReplaceAndDeleteUndeterminedNode(UndeterminedDecisionTreeNode *undeterminedNode, DecisionTreeNode *newNode);

    void SaveNode(DecisionTreeNode* node, QFile* file, int depth = 1);
private:
    QGraphicsScene *scene = nullptr;
    QGraphicsView *view = nullptr;


    DecisionTreeNode* root = nullptr;

    DecisionTreeIOManager *ioManager = nullptr;
};

#endif // DECISIONTREEEDITOR_H
