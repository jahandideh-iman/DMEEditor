#ifndef GUINODE_H
#define GUINODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>



class DecisionTreeNode : public QGraphicsItem
{

public:
    DecisionTreeNode(QGraphicsItem *parent = 0);
    ~DecisionTreeNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

protected:
    QGraphicsEllipseItem* ellipse = nullptr;

    QGraphicsTextItem* textItem = nullptr;
};

#endif // GUINODE_H
