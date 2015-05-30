#ifndef LINK_H
#define LINK_H

#include <QGraphicsObject>
#include "Utilities/MenuContributer.h"

class LinkBox;

class Link: public QGraphicsObject, public MenuContributer
{
    Q_OBJECT
public:
    Link(LinkBox *parent, LinkBox *child);
    ~Link();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QRectF boundingRect() const override;

    void ContributeToMenu(QMenu *menu) override;

    void SetLabel(QString const& label);

    LinkBox *GetChildLinkBox();
    LinkBox *GetParentLinkBox();
public slots:
    void Unlink();

private:
    QGraphicsLineItem* line = nullptr;

    LinkBox *parent;
    LinkBox *child;

    QString linkLabel = "";
};

#endif // LINK_H
