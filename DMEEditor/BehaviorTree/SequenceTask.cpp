#include "SequenceTask.h"

SequenceTask::SequenceTask()
{

    QPolygonF polygon;
    polygon << QPointF(-30, 0) << QPointF(30, 0) << QPointF( 10, 10) << QPointF(30, 0) << QPointF(10,-10) << QPointF(30, 0);
    arrow = new QGraphicsPolygonItem(polygon,this);
}

SequenceTask::~SequenceTask()
{
    delete arrow;
}

QString SequenceTask::GetType()
{
    return "SequenceTask";
}

