#include "Link.h"
#include "LinkBox.h"
#include <QPainter>
#include <QDebug>

Link::Link(LinkBox *parent, LinkBox *child)
{
    this->parent = parent;
    this->child = child;
    child->SetLink(this);
    parent->SetLink(this);

    line = new QGraphicsLineItem(this);
    setZValue(parent->zValue()-1);
}

Link::~Link()
{
    child->SetLink(nullptr);
    parent->SetLink(nullptr);
    delete line;
}

void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter;option;widget;
    line->setLine(QLineF(parent->scenePos(),child->scenePos()));

    if(linkLabel != "")
    {
        QPointF labelPos = mapFromScene(parent->scenePos() + (child->scenePos() - parent->scenePos())/2);
        painter->drawText(labelPos, linkLabel);
    }
}

QRectF Link::boundingRect() const
{
    return line->boundingRect();
}

void Link::ContributeToMenu(QMenu *menu)
{
    menu->addAction("Detach", this, SLOT(Unlink()));
}

void Link::SetLabel(const QString &label)
{
    linkLabel = label;
}

LinkBox *Link::GetChildLinkBox()
{
    return child;
}

LinkBox *Link::GetParentLinkBox()
{
    return parent;
}

void Link::Unlink()
{
    delete this;
}

