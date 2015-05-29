#ifndef BEHAVIORTREEGRAPHICSSCENE_H
#define BEHAVIORTREEGRAPHICSSCENE_H

#include <QGraphicsScene>

class BehaviorTreeEditor;
class AttachBox;

class BehaviorTreeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    BehaviorTreeGraphicsScene(BehaviorTreeEditor *editor);
    ~BehaviorTreeGraphicsScene();


    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void StartTracking(QGraphicsItem *item);
    void StopTracking();

public slots:
    void CreateActionTaskHelper();
    void CreateSelectorTaskHelper();
    void CreateSequenceTaskHelper();

private:
    BehaviorTreeEditor *editor = nullptr;

    QPoint clickPosition;

    QGraphicsLineItem *attachmentPlaceHolder = nullptr;

    QGraphicsItem* trackedItem = nullptr;
};

#endif // BEHAVIORTREEGRAPHICSSCENE_H
