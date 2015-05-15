#include "BehaviorTask.h"
#include "Application.h"
#include "BehaviorTreeEditor.h"

BehaviorTask::BehaviorTask()
{
    rect = new QGraphicsRectItem(QRect(-30,-30,60,60),this);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    rect->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

BehaviorTask::~BehaviorTask()
{
    delete rect;
}

void BehaviorTask::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;
    option;
    widget;
}

QRectF BehaviorTask::boundingRect() const
{
    return rect->boundingRect();
}

void BehaviorTask::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

void BehaviorTask::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Remove",this, SLOT(Remove()));
}

void BehaviorTask::AddChildAttachBox(bool isRemoveable)
{
    auto box = new AttachBox(AttachBox::Role_Child,this);
    box->SetRemoveable(isRemoveable);
    childAttachBoxes.push_back(box);

    RearrangeChildAttachBoxes();
}

void BehaviorTask::RemoveChildAttachBox(AttachBox *box)
{
    childAttachBoxes.removeOne(box);
    delete box;
    RearrangeChildAttachBoxes();
}

void BehaviorTask::Remove()
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->RemoveTask(this);
}

void BehaviorTask::RearrangeChildAttachBoxes()
{
    for(int i = 0 ; i < childAttachBoxes.size() ; ++i)
        childAttachBoxes[i]->setPos(i*15, 30);
}
