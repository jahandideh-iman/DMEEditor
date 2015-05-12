#include "Attachment.h"
#include "AttachBox.h"

Attachment::Attachment(AttachBox *parent, AttachBox *child)
{
    this->child = child;
    this->parent = parent;
    line = new QGraphicsLineItem(QLineF(parent->mapToScene(0,0),child->mapToScene(0,0)),this);
}

Attachment::~Attachment()
{

}

void Attachment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    line->setLine(QLineF(parent->mapToScene(0,0),child->mapToScene(0,0)));
}

QRectF Attachment::boundingRect() const
{
    return line->boundingRect();
}

