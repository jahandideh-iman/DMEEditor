#ifndef GUINODE_H
#define GUINODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "PropertyPanel.h"

class DecisionTreeNode :  public QObject ,public QGraphicsItem
{

public:
    DecisionTreeNode(QGraphicsItem *parent = 0);
    ~DecisionTreeNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;


protected:
    virtual void InitialPropertyWidgets() ;

protected:

    QGraphicsEllipseItem* ellipse = nullptr;

    QGraphicsTextItem* textItem = nullptr;

};

#endif // GUINODE_H
