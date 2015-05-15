#include "Editor.h"

Editor::Editor()
{

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

