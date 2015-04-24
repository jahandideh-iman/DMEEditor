#ifndef FINITESTATEMACHINEIOMANAGER_H
#define FINITESTATEMACHINEIOMANAGER_H

#include <QVector>
#include <rapidxml.hpp>
#include "IOManager.h"
#include <QMap>

using namespace rapidxml;

class StateNode;
class FiniteStateMachineEditor;
class QFile;

class FiniteStateMachineIOManager : public IOManager
{
    typedef  xml_node<char> XMLNode;
public:
    FiniteStateMachineIOManager();
    ~FiniteStateMachineIOManager();

    void SaveToFile(QString &fileName, Editor *editor) override;
    void ReadFromFile(QString &fileName, Editor *editor)override;
    bool IsCompatibleWith(Editor *editor) override;
    bool IsFileValid(QString &fileName) override;

private:
    void SaveStates(QFile* file);
    void SaveTransitions(QFile* file);
    void SaveRoot(QFile* file);
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
    FiniteStateMachineEditor *editor;

    QMap<QString, StateNode* > parsedStatesMap;

};

#endif // FINITESTATEMACHINEIOMANAGER_H
