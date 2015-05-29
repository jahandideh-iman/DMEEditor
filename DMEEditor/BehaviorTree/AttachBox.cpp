#include "AttachBox.h"
#include <QBrush>
#include "Core/Application.h"
#include "BehaviorTreeEditor.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "BehaviorTask.h"
#include "Attachment.h"


AttachBox::AttachBox(Role role, BehaviorTask *owner) : QGraphicsObject( owner)
{
    ownerTask = owner;
    rect.setParentItem(this);
    rect.setRect(QRect(QPoint(-5,-5), QPoint(5,5)));
    rect.setBrush(QBrush(Qt::red));
    rect.setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    this->role = role;
}

AttachBox::~AttachBox()
{
    delete attachment;
}

void AttachBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;
    option;
    widget;
}

QRectF AttachBox::boundingRect() const
{
    return rect.boundingRect();
}

void AttachBox::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsObject::mousePressEvent(mouseEvent);
    if(mouseEvent->button() == Qt::LeftButton && IsAttached() == false)
        AttachBoxSelected();
}

void AttachBox::ContributeToMenu(QMenu *menu)
{
    if(IsAttached())
        menu->addAction("Detach", this, SLOT(DettachAttachment()));
    else
        menu->addAction("Attach", this, SLOT(AttachBoxSelected()));
    if(isRemoveable)
        menu->addAction("Remove", this, SLOT(Remove()));
}

AttachBox::Role AttachBox::GetRole()
{
    return role;
}

void AttachBox::SetAttachment(Attachment *attachment)
{
    this->attachment = attachment;
}

void AttachBox::SetRemoveable(bool isRemoveable)
{
    this->isRemoveable = isRemoveable;
}

BehaviorTask *AttachBox::GetChildTask()
{
    if(role == Role_ToParent || attachment == nullptr)
        return nullptr;

    return attachment->GetChildAttachBox()->GetParentTask();
}

BehaviorTask *AttachBox::GetParentTask()
{
    return ownerTask;
}

void AttachBox::AttachBoxSelected()
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->AttachBoxSelected(this);
}

void AttachBox::DettachAttachment()
{
    ((BehaviorTreeEditor*) Application::Get()->GetEditor())->Detach(attachment);
}

void AttachBox::Remove()
{
    if(role == Role_ToChild)
        ownerTask->RemoveToChildAttachBox(this);
}

bool AttachBox::IsAttached()
{
    return attachment != nullptr;
}
