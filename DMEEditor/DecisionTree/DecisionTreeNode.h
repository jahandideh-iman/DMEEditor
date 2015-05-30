#ifndef GUINODE_H
#define GUINODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "Utilities/PropertyPanel.h"
#include "Utilities/MenuContributer.h"
#include "TreeUtilities/TreeNode.h"

class DecisionTreeNode :  public TreeNode
{

public:
    DecisionTreeNode(QGraphicsItem *parent = 0);
    virtual ~DecisionTreeNode();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

    void OnLinkBoxSelected(LinkBox *selected) override;

protected:
    virtual void InitialPropertyWidgets() ;

};

#endif // GUINODE_H
