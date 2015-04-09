#ifndef GUINODE_H
#define GUINODE_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include "PropertyPanel.h"

class DecisionTreeNode :  public QObject ,public QGraphicsItem
{

public:
    DecisionTreeNode(PropertyPanel* propertyPanel,QGraphicsItem *parent = 0);
    ~DecisionTreeNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

       QGraphicsEllipseItem* ellipse = nullptr;
protected:
    virtual void InitialPropertyWidgets() ;

protected:


    QGraphicsTextItem* textItem = nullptr;

    PropertyPanel* propertyPanel = nullptr;
};

#endif // GUINODE_H
