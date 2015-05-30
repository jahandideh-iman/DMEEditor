#ifndef EDITORGRAPHICSSCENE_H
#define EDITORGRAPHICSSCENE_H

#include <QGraphicsScene>


class Editor;
class QMenu;

class EditorGraphicsScene : public QGraphicsScene
{
public:
    EditorGraphicsScene(Editor *editor);
    virtual ~EditorGraphicsScene();

    void StartMouseTracking(QGraphicsItem *startingItem);
    void StopMouseTracking();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

protected:
    virtual void ContributeToMenu(QMenu *menu) = 0;

private:
    bool IsTrackingMouse();
    void UpdateMouseTrackingLine(QPointF scenePos);

protected:
    Editor *editor;

    QPointF clickPosition;

private:
    QGraphicsLineItem *mouseTrackingLine = nullptr;
    QGraphicsItem *mouseTrackingStartingItem = nullptr;
};

#endif // EDITORGRAPHICSSCENE_H
