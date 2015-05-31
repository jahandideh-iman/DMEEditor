#ifndef FINITESTATEMACHINEEDITOR_H
#define FINITESTATEMACHINEEDITOR_H

#include "Core/Editor.h"

class StateNode;
class StateTransition;

class FiniteStateMachineEditor : public Editor
{

public:
    FiniteStateMachineEditor();
    ~FiniteStateMachineEditor();

    void CreateState(QPointF pos);
    void RemoveState(StateNode *state);
    void AddState(StateNode* state);
    void ConnectStates(StateNode *startState, StateNode *endState);
    const QVector<StateNode *> &GetStates() const;

    void SetRootState(StateNode* node);
    StateNode *GetRootState();

    void AddTransition(StateTransition *transition);
    void RemoveTransition(StateTransition *transition);

    void OnStateSelected(StateNode *selected);
    void CancelMouseTacking() override;
    bool IsInConnectingState();

private:

    void SetConnectingState(bool state);

private:
    StateNode* rootState = nullptr;

    QVector<StateNode *> states;

    StateNode *lastSelectedNode = nullptr;

};

#endif // FINITESTATEMACHINEEDITOR_H
