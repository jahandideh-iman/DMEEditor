#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QGraphicsItem>
#include "Utilities/MenuContributer.h"

class AttachBox;

class Attachment : public QGraphicsObject, public MenuContributer
{
    Q_OBJECT
public:
    Attachment(AttachBox *parent, AttachBox *child);
    ~Attachment();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void ContributeToMenu(QMenu *menu);

    AttachBox *GetChildAttachBox();

public slots:
    void Dettach();

private:
    QGraphicsLineItem* line = nullptr;

    AttachBox *parent;
    AttachBox *child;
};

#endif // ATTACHMENT_H
