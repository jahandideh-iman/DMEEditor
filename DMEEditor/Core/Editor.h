#ifndef EDITOR_H
#define EDITOR_H

#include "QGraphicsView"
#include "EditorGraphicsScene.h"

class Editor
{
public:
    Editor();
    virtual ~Editor();

    QGraphicsView *GetView();
    QGraphicsScene *GetScene();

    virtual void CancelMouseTacking();

protected:
    QGraphicsView *view = nullptr;
    QGraphicsScene *scene = nullptr;
};

#endif // EDITOR_H
