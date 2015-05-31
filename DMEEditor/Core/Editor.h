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
    EditorGraphicsScene *GetScene();

    virtual void CancelMouseTacking();

protected:
    QGraphicsView *view = nullptr;
    EditorGraphicsScene *scene = nullptr;
};

#endif // EDITOR_H
