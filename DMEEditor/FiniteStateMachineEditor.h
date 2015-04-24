#ifndef FINITESTATEMACHINEEDITOR_H
#define FINITESTATEMACHINEEDITOR_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "FiniteStateMachineIOManager.h"
#include "Editor.h"

class StateNode;
class StateLink;
class QFile;

class FiniteStateMachineEditor : public QObject , public Editor
{
    Q_OBJECT
public:
    FiniteStateMachineEditor();
    ~FiniteStateMachineEditor();

    QGraphicsView *GetView() const;


    StateNode *GetRootNode();

    void AddNode(StateNode* node);

    void AddLink(StateLink *link);
    void DeleteLink(StateLink *link);


public slots:
    void CreateNode(QPointF pos);
    void DeleteNode(StateNode* node);
    void StartConnectingNode(StateNode* node);
    void FinishConnectingNode(StateNode* endNode);
    void CancelConnectingNode();
    void SetRootNode(StateNode* node);

private:

private:


    StateNode* rootNode = nullptr;

    StateNode* connectionStartNode = nullptr;

    FiniteStateMachineIOManager *IOManager = nullptr;


};

#endif // FINITESTATEMACHINEEDITOR_H
