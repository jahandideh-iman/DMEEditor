#include "CurvedArrow.h"
#include <QPainter>

CurvedArrow::CurvedArrow(QGraphicsItem *head, QGraphicsItem *tail, double itemsRadius,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    handle =  new QGraphicsRectItem(QRect(-5,-5,10,10), this);
    handle->setFlag(QGraphicsItem::ItemIsSelectable);
    handle->setFlag(QGraphicsItem::ItemIsMovable);

    QPointF sceneHandlePos = head->scenePos() + ((tail->scenePos() - head->scenePos()) /2) ;
    QLineF normalLine = QLineF(head->scenePos(), tail->scenePos()).normalVector();
    normalLine.setLength(100);
    sceneHandlePos += normalLine.p2() - normalLine.p1();
    handle->setPos(mapFromScene(sceneHandlePos));
    handle->setOpacity(0.15);

    path = new QGraphicsPathItem(this);
    path->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    this->head = head;
    this->tail = tail;

    this->itemsRadius = itemsRadius;

    label = new QGraphicsTextItem(this);
}

CurvedArrow::~CurvedArrow()
{
    delete handle;
    delete path;
}

void CurvedArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QPointF startPoint = head->scenePos();
    QPointF endPoint = tail->scenePos();


    QLineF tempLine(handle->scenePos(),tail->scenePos());
    tempLine.setLength(itemsRadius);

    endPoint = endPoint - (tempLine.p2() - tempLine.p1());

    tempLine.setPoints(head->scenePos(), handle->scenePos());
    tempLine.setLength(itemsRadius);

    startPoint = startPoint + (tempLine.p2() - tempLine.p1());

    QPainterPath pathPainter(mapFromScene(startPoint));
    pathPainter.quadTo(handle->pos(), mapFromScene(endPoint));
    path->setPath(pathPainter);


    QLineF line(mapFromScene(endPoint), handle->pos());
    line.setLength(20);
    line.setAngle(line.angle() + 30);
    painter->drawLine(line);
    QLineF line2(mapFromScene(endPoint), handle->pos());
    line2.setLength(20);
    line2.setAngle(line2.angle() - 30);
    painter->drawLine(line2);

    QPointF labelPos(-label->boundingRect().width()/2 , -label->boundingRect().height()/2);
    QPointF sceneMiddlePos = head->scenePos() + ((tail->scenePos() - head->scenePos()) /2) ;

    labelPos+= handle->pos() - (handle->pos() - mapFromScene(sceneMiddlePos)) / 3;

    label->setPos(labelPos);
}

QRectF CurvedArrow::boundingRect() const
{
    return path->boundingRect();
}

void CurvedArrow::SetLabelName(const QString &name)
{
    label->setPlainText(name);
}

QPointF CurvedArrow::GetHandlePos()
{
    return handle->scenePos();
}

void CurvedArrow::SetHandleScenePos(float x, float y)
{
    handle->setPos(mapFromScene(x,y));
}

