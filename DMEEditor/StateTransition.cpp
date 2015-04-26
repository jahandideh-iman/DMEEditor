#include "StateTransition.h"
#include "StateNode.h"
#include <QDebug>
#include <QGraphicsScene>
#include "MainWindow.h"
#include "StringProperty.h"

StateTransition::StateTransition(StateNode *startNode, StateNode *endNode, QString condition)
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

StateTransition::~StateTransition()
{
    RemoveFromStates();
    delete rect;
    delete path;
    delete pathPainter;
}

void StateTransition::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void StateTransition::InitialPropertyWidgets()
{
    MainWindow::GetPropertyPanel()->Clear();
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("Condtion", conditionName,this,SLOT(SetConditionName(const QString& ))));

}


void StateTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF StateTransition::boundingRect() const
{
    return path->boundingRect();
}

StateNode *StateTransition::GetStartNode()
{
    return startNode;
}

StateNode *StateTransition::GetEndNode()
{
    return endNode;
}

void StateTransition::RemoveFromStates()
{
    endNode->RemoveInLink(this);
    startNode->RemoveOutLink(this);
}

QString StateTransition::GetConditionName()
{
    return conditionName;
}

void StateTransition::SetConditionName(const QString &value)
{
    conditionName = value;
}
