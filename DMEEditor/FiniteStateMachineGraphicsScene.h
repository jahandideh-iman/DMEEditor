#ifndef FINITESTATEMACHINEGRAPHICSSCENE_H
#define FINITESTATEMACHINEGRAPHICSSCENE_H

#include <QGraphicsScene>

class FiniteStateMachineEditor;
class StateNode;
class StateTransition;

class FiniteStateMachineGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    FiniteStateMachineGraphicsScene(FiniteStateMachineEditor* editor);
    ~FiniteStateMachineGraphicsScene();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;

public slots:
    void CreateNodeHelper();
    void DeleteNodeHelper();
    void StartConnectingNodeHelper();
    void FinishConnectingNodeHelper(StateNode* endNode);
    void CancelConnectingNodeHelper();
    void SetRootNodeHelper();

    void DeleteLinkHelper();

private:
    void ShowContextMenu(QGraphicsSceneContextMenuEvent *event);
    void ShowContextMenuForNode(QGraphicsSceneContextMenuEvent *event, StateNode* node);
    void ShowContextMenuForLink(QGraphicsSceneContextMenuEvent *event, StateTransition* link);

    FiniteStateMachineEditor* editor;

    QPointF contexMenuPosition;
    StateNode* selectedNode = nullptr;
    StateTransition* selectedLink = nullptr;

    QGraphicsLineItem* connectionPlaceHolder = nullptr;

    bool isInConnectingState = false;
};

#endif // FINITESTATEMACHINEGRAPHICSSCENE_H
