#include "StateNode.h"
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include "StateLink.h"
#include "MainWindow.h"
#include "StringProperty.h"



StateNode::StateNode(QString name, QString updateAction, QString entryAction, QString exitAction)
{

    ellipse = new QGraphicsEllipseItem(this);
    ellipse->setRect(QRect(-25,-25,50,50));

    ellipse->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    stateNameTextItem = new QGraphicsTextItem(GetStateName(),this);
    stateNameTextItem->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    SetStateName(name);
    SetUpdateActionName(updateAction);
    SetEntryActionName(entryAction);
    SetExitActionName(exitAction);

}

StateNode::~StateNode()
{
    scene()->removeItem(this);
    outLinkes.clear();
    inLinkes.clear();
}

void StateNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void StateNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;
    option;
    widget;
//    for(auto child : children)
//    {
//        painter->drawLine(QPointF(0,0), child->pos() - pos());
//    }
}

QRectF StateNode::boundingRect() const
{
    return ellipse->boundingRect();
}

void StateNode::AddOutLink(StateLink *link)
{
    outLinkes.push_back(link);
}

void StateNode::AddInLink(StateLink *link)
{
    inLinkes.push_back(link);
}

void StateNode::RemoveOutLink(StateLink *link)
{
    outLinkes.removeOne(link);
}

void StateNode::RemoveInLink(StateLink *link)
{
    inLinkes.removeOne(link);
}

QVector<StateLink *> &StateNode::GetOutLinks()
{
    return outLinkes;
}

QVector<StateLink *> &StateNode::GetInLinks()
{
    return inLinkes;
}

void StateNode::SetRootFlag(bool flag)
{
    isRoot = flag;
    if(isRoot)
        ellipse->setBrush(QBrush(Qt::red));
    else
        ellipse->setBrush(QBrush(Qt::white));
}

bool StateNode::IsRoot()
{
    return isRoot;
}

QString StateNode::GetStateName()
{
    return stateName;
}

QString StateNode::GetUpdateActionName()
{
    return updateActionName;
}

QString StateNode::GetEntryActionName()
{
    return entryActionName;
}

QString StateNode::GetExitActionName()
{
    return exitActionName;
}

void StateNode::SetStateName(const QString &value)
{
    stateName = value;
    stateNameTextItem->setPlainText(stateName);
}

void StateNode::SetUpdateActionName(const QString &value)
{
    updateActionName = value;
}

void StateNode::SetEntryActionName(const QString &value)
{
    entryActionName = value;
}

void StateNode::SetExitActionName(const QString &value)
{
    exitActionName = value;
}

void StateNode::InitialPropertyWidgets()
{
    MainWindow::GetPropertyPanel()->Clear();
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("Name", stateName,this,SLOT(SetStateName(const QString& ))));
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("State Action", updateActionName,this,SLOT(SetUpdateActionName(const QString& ))));
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("Exit Action", exitActionName,this,SLOT(SetExitActionName(const QString& ))));
    MainWindow::GetPropertyPanel()->AddProperty(new StringProperty("Entry Action", entryActionName,this,SLOT(SetEntryActionName(const QString& ))));

}





