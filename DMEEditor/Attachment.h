#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QGraphicsItem>

class AttachBox;

class Attachment : public QGraphicsItem
{
public:
    Attachment(AttachBox *parent, AttachBox *child);
    ~Attachment();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:
    QGraphicsLineItem* line = nullptr;

    AttachBox *parent;
    AttachBox *child;
};

#endif // ATTACHMENT_H
