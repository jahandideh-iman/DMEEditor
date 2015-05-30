#include "Editor.h"

Editor::Editor()
{
    view = new QGraphicsView(scene);

    view->setSceneRect(0,0,1000,1000);
    view->setMouseTracking(true);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setAlignment(Qt::AlignTop);
}

Editor::~Editor()
{
    delete view;
    delete scene;
}

QGraphicsView *Editor::GetView()
{
    return view;

}

QGraphicsScene *Editor::GetScene()
{
    return scene;
}

void Editor::CancelMouseTacking()
{

}

