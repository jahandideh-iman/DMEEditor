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

public slots:
    void CreateActionTaskHelper();
    void StartAttachingHelper();
    void CancelAttachingHelper();
    void FinishAttachingHelper(AttachBox *box);

private:
    BehaviorTreeEditor *editor = nullptr;

    QGraphicsLineItem *attachmentPlaceHolder = nullptr;
    bool isInAttachingState = false;
    AttachBox *selectedAttachBox;
};

#endif // BEHAVIORTREEGRAPHICSSCENE_H
