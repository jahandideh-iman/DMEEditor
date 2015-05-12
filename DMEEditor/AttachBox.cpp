#include "AttachBox.h"
#include <QBrush>

AttachBox::AttachBox(Role role,QGraphicsItem *parent) : QGraphicsRectItem( parent)
{
    setRect(QRect(QPoint(-5,-5), QPoint(5,5)));
    setBrush(QBrush(Qt::red));
    this->role = role;
}

AttachBox::~AttachBox()
{

}

AttachBox::Role AttachBox::GetRole()
{
    return role;
}

