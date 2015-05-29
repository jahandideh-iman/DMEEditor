#include "BehaviorTask.h"
#include "Core/Application.h"
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


void BehaviorTask::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Remove",this, SLOT(Remove()));
}

AttachBox *BehaviorTask::GetToParentAttachBox()
{
    return toParentAttachBox;
}

void BehaviorTask::AddToChildAttachBox(bool isRemoveable)
{
    auto box = new AttachBox(AttachBox::Role_ToChild,this);
    box->SetRemoveable(isRemoveable);
    toChildAttachBoxes.push_back(box);

    RearrangeToChildAttachBoxes();
}

void BehaviorTask::RemoveToChildAttachBox(AttachBox *box)
{
    toChildAttachBoxes.removeOne(box);
    delete box;
    RearrangeToChildAttachBoxes();
}

void BehaviorTask::Remove()
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->RemoveTask(this);
}

void BehaviorTask::RearrangeToChildAttachBoxes()
{
    for(int i = 0 ; i < toChildAttachBoxes.size() ; ++i)
        toChildAttachBoxes[i]->setPos(i*15, 30);
}
