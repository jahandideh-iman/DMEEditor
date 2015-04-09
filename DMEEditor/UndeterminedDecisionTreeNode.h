#ifndef UNKOWNDECISIONTREENODE_H
#define UNKOWNDECISIONTREENODE_H

#include "DecisionTreeNode.h"
#include "DecisionNode.h"
#include <QMenu>

class DecisionTreeEditor;




class UndeterminedDecisionTreeNode :public DecisionTreeNode
{
    Q_OBJECT
public:
    UndeterminedDecisionTreeNode(DecisionTreeEditor* editor, DecisionNode* parentNode, PropertyPanel* propertyPanel);
    ~UndeterminedDecisionTreeNode();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    DecisionNode *getParentNode();

public slots:
    void ConvertToActionNode();
    void ConvertToDecisionNode();

private:
    DecisionTreeEditor* editor = nullptr;

    DecisionNode* parentNode = nullptr;


};

#endif // UNKOWNDECISIONTREENODE_H
