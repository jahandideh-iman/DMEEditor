#ifndef CURVEDARROW_H
#define CURVEDARROW_H

#include <QGraphicsItem>

class CurvedArrow : public QGraphicsItem
{
public:
    CurvedArrow(QGraphicsItem *head, QGraphicsItem *tail, double itemsRadius, QGraphicsItem *parent);
    ~CurvedArrow();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void SetLabelName(QString const &name);

    QPointF GetHandlePos();
    void SetHandleScenePos(float x, float y);

private:
    QGraphicsPathItem* path = nullptr;
    QGraphicsRectItem *handle = nullptr;

    QGraphicsItem *head = nullptr;
    QGraphicsItem *tail = nullptr;

    double itemsRadius;

    QGraphicsTextItem *label = nullptr;
};

#endif // CURVEDARROW_H
