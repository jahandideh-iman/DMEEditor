#ifndef FINITESTATEMACHINEGRAPHICSSCENE_H
#define FINITESTATEMACHINEGRAPHICSSCENE_H

#include "Core/EditorGraphicsScene.h"

class FiniteStateMachineEditor;
class StateNode;
class StateTransition;

class FiniteStateMachineGraphicsScene : public EditorGraphicsScene
{
    Q_OBJECT
public:
    FiniteStateMachineGraphicsScene(FiniteStateMachineEditor* editor);
    ~FiniteStateMachineGraphicsScene();

public slots:
    void CreateNodeHelper();

protected:
    void ContributeToMenu(QMenu *menu);

private:

    FiniteStateMachineEditor *GetEditor();

};

#endif // FINITESTATEMACHINEGRAPHICSSCENE_H
