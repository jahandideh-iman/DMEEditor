#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "DecisionTreeNode.h"
#include "StringProperty.h"

class ActionNode : public DecisionTreeNode
{
    Q_OBJECT
public:
    ActionNode(PropertyPanel* propertyPanel);
    ~ActionNode();

    QString GetActionName();

protected:
    void InitialPropertyWidgets() override;

public slots:
    void ActionNameChanged(const QString& value);

private:
    void SetActionName(QString value);

private:
    QString actionName;
};

#endif // ACTIONNODE_H

