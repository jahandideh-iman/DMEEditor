#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T13:19:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DMEEditor
TEMPLATE = app


SOURCES += main.cpp\
    BehaviorTree/ActionTask.cpp \
    BehaviorTree/BehaviorTask.cpp \
    BehaviorTree/BehaviorTreeEditor.cpp \
    BehaviorTree/BehaviorTreeGraphicsScene.cpp \
    BehaviorTree/BehaviorTreeIOManager.cpp \
    BehaviorTree/CompoundTask.cpp \
    Core/Application.cpp \
    Core/Editor.cpp \
    Core/IOManager.cpp \
    DecisionTree/ActionNode.cpp \
    DecisionTree/DecisionNode.cpp \
    DecisionTree/DecisionTreeEditor.cpp \
    DecisionTree/DecisionTreeIOManager.cpp \
    DecisionTree/DecisionTreeNode.cpp \
    FiniteStateMachine/FiniteStateMachineEditor.cpp \
    FiniteStateMachine/FiniteStateMachineGraphicsScene.cpp \
    FiniteStateMachine/FiniteStateMachineIOManager.cpp \
    FiniteStateMachine/StateNode.cpp \
    FiniteStateMachine/StateTransition.cpp \
    Utilities/PropertyPanel.cpp \
    Utilities/PropertyWidget.cpp \
    Utilities/StringProperty.cpp \
    DecisionTree/DecisionTreeGraphicsScene.cpp \
    TreeUtilities/Link.cpp \
    TreeUtilities/LinkBox.cpp \
    TreeUtilities/TreeNode.cpp \
    Core/EditorGraphicsScene.cpp \
    BehaviorTree/SequenceTask.cpp \
    BehaviorTree/SelectorTask.cpp \
    FiniteStateMachine/CurvedArrow.cpp

HEADERS  += \
    BehaviorTree/ActionTask.h \
    BehaviorTree/BehaviorTask.h \
    BehaviorTree/BehaviorTreeEditor.h \
    BehaviorTree/BehaviorTreeGraphicsScene.h \
    BehaviorTree/BehaviorTreeIOManager.h \
    BehaviorTree/CompoundTask.h \
    Core/Application.h \
    Core/Editor.h \
    Core/IOManager.h \
    DecisionTree/ActionNode.h \
    DecisionTree/DecisionNode.h \
    DecisionTree/DecisionTreeEditor.h \
    DecisionTree/DecisionTreeIOManager.h \
    DecisionTree/DecisionTreeNode.h \
    FiniteStateMachine/FiniteStateMachineEditor.h \
    FiniteStateMachine/FiniteStateMachineGraphicsScene.h \
    FiniteStateMachine/FiniteStateMachineIOManager.h \
    FiniteStateMachine/StateNode.h \
    FiniteStateMachine/StateTransition.h \
    Utilities/MenuContributer.h \
    Utilities/PropertyPanel.h \
    Utilities/PropertyWidget.h \
    Utilities/rapidxml.hpp \
    Utilities/StringProperty.h \
    DecisionTree/DecisionTreeGraphicsScene.h \
    TreeUtilities/Link.h \
    TreeUtilities/LinkBox.h \
    TreeUtilities/TreeNode.h \
    Core/EditorGraphicsScene.h \
    BehaviorTree/SequenceTask.h \
    BehaviorTree/SelectorTask.h \
    FiniteStateMachine/CurvedArrow.h

FORMS    += mainwindow.ui
