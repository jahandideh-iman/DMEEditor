#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include "DecisionTreeNode.h"
#include "Utilities/StringProperty.h"

class DecisionNode : public DecisionTreeNode
{
    Q_OBJECT
public:

    DecisionNode(QGraphicsItem *parent = 0);
    ~DecisionNode();

    DecisionTreeNode *GetLeftChild();
    DecisionTreeNode *GetRightChild();

    QString GetConditionName();

    void OnLinkBoxLinked(LinkBox *box, Link *link);


    LinkBox *GetLeftChildBox();
    LinkBox *GetRightChildBox();

protected:
    void InitialPropertyWidgets() override;

    void RearrangeToChildLinkBoxes() override;
    void RearrangeToParentLinkBox() override;

public slots:
    void SetConditionName(const QString& value);

private:


private:
    QString conditionName;

    const int shapeWidth = 40;
    const int shapeHeight = 40;
};

#endif // DECISIONNODE_H
