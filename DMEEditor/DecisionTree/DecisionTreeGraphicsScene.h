#ifndef DECISIONTREEGRAPHICSSCENE_H
#define DECISIONTREEGRAPHICSSCENE_H

#include <QGraphicsScene>

class DecisionTreeEditor;

class DecisionTreeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DecisionTreeGraphicsScene(DecisionTreeEditor *editor);
    ~DecisionTreeGraphicsScene();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

    void StartMouseTracking(QGraphicsItem *startingItem);
    void StopMouseTracking();

public slots:
    void CreateActionNodeHelper();
    void CreateDicisionNodeHelper();

private:
    bool IsTrackingMouse();

    void UpdateMouseTrackingLine(QPointF scenePos);

private:
    DecisionTreeEditor *editor = nullptr;

    QPointF clickPosition;

    QGraphicsLineItem *mouseTrackingLine = nullptr;
    QGraphicsItem* mouseTrackingStartingItem = nullptr;
};

#endif // DECISIONTREEGRAPHICSSCENE_H
