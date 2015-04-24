#ifndef EDITOR_H
#define EDITOR_H

#include "QGraphicsView"

class Editor
{
public:
    Editor();
    virtual ~Editor();

    QGraphicsView *GetView();

protected:
    QGraphicsView *view = nullptr;
    QGraphicsScene *scene = nullptr;
};

#endif // EDITOR_H
