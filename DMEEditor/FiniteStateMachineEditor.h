#ifndef FINITESTATEMACHINEEDITOR_H
#define FINITESTATEMACHINEEDITOR_H

#include "Editor.h"

class StateNode;
class StateTransition;

class FiniteStateMachineEditor : public Editor
{

public:
    FiniteStateMachineEditor();
    ~FiniteStateMachineEditor();

    void CreateState(QPointF pos);
    void DeleteState(StateNode *state);
    void AddState(StateNode* state);
    void ConnectStates(StateNode *startState, StateNode *endState);
    const QVector<StateNode *> &GetStates() const;

    void SetRootState(StateNode* node);
    StateNode *GetRootState();

    void AddTransition(StateTransition *transition);
    void DeleteTransition(StateTransition *transition);

private:
    StateNode* rootState = nullptr;

    QVector<StateNode *> states;

};

#endif // FINITESTATEMACHINEEDITOR_H
