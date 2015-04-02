#ifndef GUINODE_H
#define GUINODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>


class Node : public QGraphicsItem
{
public:
    Node(QGraphicsItem *parent = 0);
    ~Node();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

protected:
    QGraphicsEllipseItem* ellipse = nullptr;
};

#endif // GUINODE_H
