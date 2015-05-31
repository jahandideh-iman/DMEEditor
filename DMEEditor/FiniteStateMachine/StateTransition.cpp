#include "StateTransition.h"
#include "StateNode.h"
#include "Core/Application.h"
#include "Utilities/StringProperty.h"
#include "FiniteStateMachineEditor.h"
#include "CurvedArrow.h"

StateTransition::StateTransition(StateNode *startNode, StateNode *endNode, QString condition)
{
    this->setZValue(startNode->zValue()+1);
    this->startNode = startNode;
    this->endNode = endNode;

    startNode->AddOutLink(this);
    endNode->AddInLink(this);

    setPos(mapFromScene(startNode->scenePos()));

    arrow = new CurvedArrow(startNode, endNode, startNode->GetRadius() ,this);
    arrow->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    SetConditionName(condition);
}

StateTransition::~StateTransition()
{
    RemoveFromStates();
    delete arrow;
}

void StateTransition::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    InitialPropertyWidgets();
}

void StateTransition::InitialPropertyWidgets()
{
    Application::GetPropertyPanel()->Clear();
    Application::GetPropertyPanel()->AddProperty(new StringProperty("Condtion", conditionName,this,SLOT(SetConditionName(const QString& ))));

}

void StateTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;widget;option;
}

QRectF StateTransition::boundingRect() const
{
    return arrow->boundingRect();
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

void StateTransition::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Remove", this, SLOT(Remove()));
}

QPointF StateTransition::GetHandlePos()
{
    return arrow->GetHandlePos();
}

void StateTransition::SetHandlePos(float x, float y)
{
    arrow->SetHandleScenePos(x,y);
}

void StateTransition::Remove()
{
    ((FiniteStateMachineEditor*) Application::Get()->GetEditor())->RemoveTransition(this);
}

void StateTransition::SetConditionName(const QString &value)
{
    conditionName = value;
    arrow->SetLabelName(conditionName);
}
