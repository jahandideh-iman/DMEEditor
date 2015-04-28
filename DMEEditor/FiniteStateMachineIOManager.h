#ifndef FINITESTATEMACHINEIOMANAGER_H
#define FINITESTATEMACHINEIOMANAGER_H


#include "IOManager.h"
#include <QMap>



class StateNode;
class FiniteStateMachineEditor;
class QFile;

class FiniteStateMachineIOManager : public IOManager
{

public:
    FiniteStateMachineIOManager();
    ~FiniteStateMachineIOManager();

    bool IsCompatibleWith(Editor *editor) override;

protected:
    void Save(Editor *editor_) override;
    void Parse(XMLNode* rootXMLNode, Editor* editor) override;

    QString GetType() override;

private:
    void SaveStates();
    void SaveTransitions();
    void SaveRoot();
    QVector<StateNode *> GetBreadthFirstTraversal();


    void ParseStates(XMLNode* statesXMLNode);
    void ParseState(XMLNode * stateXMLNode);
    void ParseStatePosition(StateNode *node, XMLNode *stateXMLNode);
    void ParseStateEntryAction(StateNode *node, XMLNode *entryActionXMLNode);
    void ParseStateUpdateAction(StateNode *node, XMLNode *updateActionXMLNode);
    void ParseStateExitAction(StateNode *node, XMLNode *exitActionXMLNode);

    void ParseTransitions(XMLNode *transitionsXMLNode);
    void ParseTransition(XMLNode *transitionXMLNode);
    void ParseInitialState(XMLNode *initalStateXMLNode);

private:
    FiniteStateMachineEditor *editor = nullptr;

    QMap<QString, StateNode* > parsedStatesMap;

};

#endif // FINITESTATEMACHINEIOMANAGER_H
