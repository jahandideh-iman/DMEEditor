#include "DecisionNode.h"
#include <QPainter>
#include "Core/Application.h"


DecisionNode::DecisionNode(QGraphicsItem *parent) : DecisionTreeNode(parent)
{
    SetConditionName("Condition");

    QPolygonF polygon;
    polygon << QPointF(-shapeWidth, 0) << QPointF(0, -shapeHeight) << QPointF(shapeWidth, 0) << QPointF(0,shapeHeight);
    QGraphicsPolygonItem *diamond = new QGraphicsPolygonItem(polygon);

    SetShape(diamond);

    InitialToParentLinkBox();
    AddAUnremoveableToChildLinkBox();
    AddAUnremoveableToChildLinkBox();
    SetLinkBoxesLock(true);
}

DecisionNode::~DecisionNode()
{
}

DecisionTreeNode *DecisionNode::GetLeftChild()
{
    return dynamic_cast<DecisionTreeNode*> (GetLeftChildBox()->GetChildNode());
}

DecisionTreeNode *DecisionNode::GetRightChild()
{
    return dynamic_cast<DecisionTreeNode*> (GetRightChildBox()->GetChildNode());
}

QString DecisionNode::GetConditionName()
{
    return conditionName;
}

void DecisionNode::OnLinkBoxLinked(LinkBox *box, Link *link)
{
    if(box == GetLeftChildBox())
        link->SetLabel("False");
    else if(box == GetRightChildBox())
        link->SetLabel("True");
}

void DecisionNode::InitialPropertyWidgets()
{
    DecisionTreeNode::InitialPropertyWidgets();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Condition Name", conditionName,this,SLOT(SetConditionName(const QString& ))));
}

void DecisionNode::RearrangeToChildLinkBoxes()
{
    if(GetLeftChildBox() != nullptr)
        GetLeftChildBox()->setPos(-shapeWidth,0);

    if(GetRightChildBox() != nullptr)
        GetRightChildBox()->setPos(shapeWidth,0);
}

void DecisionNode::RearrangeToParentLinkBox()
{
    GetToParentLinkBox()->setPos(0,-shapeHeight);
}


void DecisionNode::SetConditionName(const QString &value)
{
    conditionName = value;
    SetNodeName(value);
}

LinkBox *DecisionNode::GetLeftChildBox()
{
    return GetToChildLinkBox(0);
}

LinkBox *DecisionNode::GetRightChildBox()
{
    return GetToChildLinkBox(1);
}

