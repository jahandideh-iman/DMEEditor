#ifndef EDITOR_H
#define EDITOR_H

#include "QGraphicsView"

class Editor
{
public:
    Editor();
    virtual ~Editor();

    QGraphicsView *GetView();
    QGraphicsScene *GetScene();

protected:
    QGraphicsView *view = nullptr;
    QGraphicsScene *scene = nullptr;
};

#endif // EDITOR_H
