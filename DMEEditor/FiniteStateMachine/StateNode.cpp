#include "StateNode.h"

#include "StateTransition.h"
#include "Core/Application.h"
#include "Utilities/StringProperty.h"
#include "FiniteStateMachine/FiniteStateMachineEditor.h"
#include "QGraphicsSceneMouseEvent"


StateNode::StateNode(QString name, QString updateAction, QString entryAction, QString exitAction)
{

    circle = new Circle(30,this);
    circle->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    circle->setFlag(QGraphicsItem::ItemIsSelectable, true);

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
    auto inLinksCopy (inLinks);
    for(auto l : inLinksCopy)
        delete l;

    auto outLinksCopy (outLinks);
    for(auto l : outLinksCopy)
        delete l;

    delete circle;
    delete stateNameTextItem;
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
    return circle->boundingRect();
}

void StateNode::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsObject::mousePressEvent(mouseEvent);
    if(mouseEvent->button() == Qt::LeftButton && EditorIsInConnectingState())
        Connect();
}

void StateNode::AddOutLink(StateTransition *link)
{
    outLinks.push_back(link);
}

void StateNode::AddInLink(StateTransition *link)
{
    inLinks.push_back(link);
}

void StateNode::RemoveOutLink(StateTransition *link)
{
    outLinks.removeAll(link);
}

void StateNode::RemoveInLink(StateTransition *link)
{
    inLinks.removeAll(link);
}

QVector<StateTransition *> &StateNode::GetOutLinks()
{
    return outLinks;
}

QVector<StateTransition *> &StateNode::GetInLinks()
{
    return inLinks;
}

void StateNode::SetRootFlag(bool flag)
{
    isRoot = flag;
    if(isRoot)
        circle->setBrush(QBrush(Qt::yellow));
    else
        circle->setBrush(QBrush(Qt::white));
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

void StateNode::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Connect",this, SLOT(Connect()));
    menu->addAction("Remove", this, SLOT(Remove()));
    if(IsRoot() == false)
        menu->addAction("Set As Root",this, SLOT(SetAsRoot()));
}

double StateNode::GetRadius()
{
    return circle->GetRadius();
}

void StateNode::Connect()
{
    ((FiniteStateMachineEditor*) Application::Get()->GetEditor())->OnStateSelected(this);
}

void StateNode::Remove()
{
    ((FiniteStateMachineEditor*) Application::Get()->GetEditor())->RemoveState(this);
}

void StateNode::SetAsRoot()
{
    ((FiniteStateMachineEditor*) Application::Get()->GetEditor())->SetRootState(this);
}

void StateNode::SetStateName(const QString &value)
{
    stateName = value;
    stateNameTextItem->setPlainText(stateName);
    float scale = 1;
    stateNameTextItem->setScale(scale);
    stateNameTextItem->setPos(-stateNameTextItem->boundingRect().width()/2 * scale, -stateNameTextItem->boundingRect().height()/2 * scale);
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
    Application::GetPropertyPanel()->Clear();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Name", stateName,this,SLOT(SetStateName(const QString& ))));
    Application::GetPropertyPanel()->AddProperty(new StringProperty("State Action", updateActionName,this,SLOT(SetUpdateActionName(const QString& ))));
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Exit Action", exitActionName,this,SLOT(SetExitActionName(const QString& ))));
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Entry Action", entryActionName,this,SLOT(SetEntryActionName(const QString& ))));

}

bool StateNode::EditorIsInConnectingState()
{
    return ((FiniteStateMachineEditor*) Application::Get()->GetEditor())->IsInConnectingState();
}





