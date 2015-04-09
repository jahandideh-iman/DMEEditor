#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include "DecisionTreeNode.h"
#include "StringProperty.h"

class DecisionNode : public DecisionTreeNode
{
    Q_OBJECT
public:

    DecisionNode(PropertyPanel* propertyPanel);
    ~DecisionNode();

    void SetLeftChild(DecisionTreeNode* leftChild);
    void SetRightChild(DecisionTreeNode* rightChild);

    void ReplaceChild(DecisionTreeNode* child, DecisionTreeNode* newNode);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

protected:
    void InitialPropertyWidgets() override;

public slots:
    void ConditionNameChanged(const QString& value);

private:
    void SetConditionName(QString value);

private:
    QString conditionName;

    DecisionTreeNode* leftChild = nullptr;
    DecisionTreeNode* rightChild = nullptr;
};

#endif // DECISIONNODE_H
