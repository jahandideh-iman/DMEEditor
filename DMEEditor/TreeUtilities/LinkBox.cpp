#include "LinkBox.h"
#include <QBrush>
#include "TreeNode.h"
#include <QGraphicsSceneMouseEvent>

LinkBox::LinkBox(Role role, TreeNode *owner /*= nullptr*/) : QGraphicsObject(owner)
{
    this->role = role;
    this->ownerNode = owner;

    rect.setParentItem(this);
    rect.setRect(QRect(QPoint(-4,-4), QPoint(4,4)));
    rect.setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    if(role == Role_ToChild)
        rect.setBrush(QBrush(Qt::black));
    else if( role == Role_ToParent)
        rect.setBrush(QBrush(Qt::red));
}

LinkBox::~LinkBox()
{
    delete link;
}

void LinkBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter; option; widget;
}

QRectF LinkBox::boundingRect() const
{
    return rect.boundingRect();
}

void LinkBox::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsObject::mousePressEvent(mouseEvent);
    if(mouseEvent->button() == Qt::LeftButton && IsLinked() == false)
        Select();
}

void LinkBox::SetRemoveable(bool isRemoveable)
{
    this->isRemoveable = isRemoveable;
}

bool LinkBox::IsRemoveable()
{
    return isRemoveable;
}

void LinkBox::SetLink(Link *link)
{
    this->link = link;
    if(link != nullptr)
        ownerNode->OnLinkBoxLinked(this, link);
}

bool LinkBox::IsLinked()
{
    return link != nullptr;
}

bool LinkBox::IsChild()
{
    return role == Role_ToParent;
}

bool LinkBox::IsParent()
{
    return role == Role_ToChild;
}

TreeNode *LinkBox::GetChildNode()
{
    if(IsChild() || !IsLinked())
        return nullptr;

    return link->GetChildLinkBox()->GetOwnerNode();
}
void LinkBox::ContributeToMenu(QMenu *menu)
{
    if(IsLinked())
        menu->addAction("Detach", this, SLOT(Unlink()));
    else
        menu->addAction("Attach", this, SLOT(Select()));

    if(IsRemoveable())
        menu->addAction("Remove", this, SLOT(Remove()));
}

void LinkBox::Select()
{
    ownerNode->OnLinkBoxSelected(this);
}

void LinkBox::Unlink()
{
    delete link;
}

void LinkBox::Remove()
{

}

TreeNode *LinkBox::GetOwnerNode()
{
    return ownerNode;
}

