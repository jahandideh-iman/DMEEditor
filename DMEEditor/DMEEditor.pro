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
    UndeterminedDecisionTreeNode.cpp \
    DecisionTreeNode.cpp \
    DecisionTreeEditor.cpp \
    DecisionNode.cpp \
    ActionNode.cpp \
    PropertyPanel.cpp \
    StringProperty.cpp \
    PropertyWidget.cpp \
    FiniteStateMachineEditor.cpp \
    FiniteStateMachineGraphicsScene.cpp \
    StateNode.cpp \
    FiniteStateMachineIOManager.cpp \
    DecisionTreeIOManager.cpp \
    Editor.cpp \
    IOManager.cpp \
    StateTransition.cpp \
    BehaviorTreeEditor.cpp \
    BehaviorTreeGraphicsScene.cpp \
    ActionTask.cpp \
    BehaviorTask.cpp \
    AttachBox.cpp \
    Attachment.cpp \
    CompoundTask.cpp \
    Application.cpp \
    BehaviorTreeIOManager.cpp

HEADERS  += \
    UndeterminedDecisionTreeNode.h \
    DecisionTreeNode.h \
    DecisionTreeEditor.h \
    DecisionNode.h \
    ActionNode.h \
    PropertyPanel.h \
    StringProperty.h \
    PropertyWidget.h \
    FiniteStateMachineEditor.h \
    FiniteStateMachineGraphicsScene.h \
    StateNode.h \
    FiniteStateMachineIOManager.h \
    rapidxml.hpp \
    DecisionTreeIOManager.h \
    Editor.h \
    IOManager.h \
    StateTransition.h \
    BehaviorTreeEditor.h \
    BehaviorTreeGraphicsScene.h \
    ActionTask.h \
    BehaviorTask.h \
    AttachBox.h \
    Attachment.h \
    CompoundTask.h \
    Application.h \
    MenuContributer.h \
    BehaviorTreeIOManager.h

FORMS    += mainwindow.ui
