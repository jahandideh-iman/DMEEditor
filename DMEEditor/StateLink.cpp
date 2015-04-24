#include "StateLink.h"
#include "StateNode.h"
#include <QDebug>
#include <QGraphicsScene>
#include "MainWindow.h"
#include "StringProperty.h"

StateLink::StateLink(StateNode *startNode, StateNode *endNode, QString condition)
{
    this->setZValue(-10);
    this->startNode = startNode;
    this->endNode = endNode;

    rect =  new QGraphicsRectItem(QRect(-5,-5,10,10), this);
    rect->setFlag(QGraphicsItem::ItemIsSelectable);
    rect->setFlag(QGraphicsItem::ItemIsMovable);

    SetConditionName(condition);


    startNode->AddOutLink(this);
    endNode->AddInLink(this);

    pathPainter  = new QPainterPath(startNode->pos());


    path = new QGraphicsPathItem(*pathPainter,this);
    path->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    //line = new QGraphicsLineItem(this);

    //line->setLine(QLineF(endNode->pos(), startNode->pos()));
    //line->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

StateLink::~StateLink()
{
    endNode->RemoveInLink(this);
    startNode->RemoveOutLink(this);
//    delete line;
//    line = nullptr;
}

void StateLink::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void StateLink::InitialPropertyWidgets()
{
    MainWindow::GetPropertyPanel()->Clear();
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("Condtion", conditionName,this,SLOT(SetConditionName(const QString& ))));

}


void StateLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option;
    widget;
    //pathPainter->
    QPainterPath pathPainter(startNode->pos());
    pathPainter.quadTo(rect->pos(), endNode->pos());
    path->setPath(pathPainter);

    QLineF line(endNode->pos(), rect->pos());
    line.setLength(20);
    line.setAngle(line.angle() + 30);
    painter->drawLine(line);
    QLineF line2(endNode->pos(), rect->pos());
    line2.setLength(20);
    line2.setAngle(line2.angle() - 30);
    painter->drawLine(line2);
    //painter->drawPolygon(points,3);
    //painter->drawPath(path->path().);
    //path->path().quadTo(QPoint(0,0), endNode->pos());
    //path->setPath();

}

QRectF StateLink::boundingRect() const
{
    return path->boundingRect();
}

StateNode *StateLink::GetStartNode()
{
    return startNode;
}

StateNode *StateLink::GetEndNode()
{
    return endNode;
}

QString StateLink::GetConditionName()
{
    return conditionName;
}

void StateLink::SetConditionName(const QString &value)
{
    conditionName = value;
}





