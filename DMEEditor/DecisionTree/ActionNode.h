#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "DecisionTreeNode.h"
#include "Utilities/StringProperty.h"

class ActionNode : public DecisionTreeNode
{
    Q_OBJECT

public:
    ActionNode(QGraphicsItem *parent = 0);
    ~ActionNode();

    QString GetActionName();

protected:
    void InitialPropertyWidgets() override;

    void RearrangeToParentLinkBox() override;

public slots:
    void SetActionName(const QString& name);

};

#endif // ACTIONNODE_H

