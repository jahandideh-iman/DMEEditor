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
    StateLink.cpp \
    FiniteStateMachineIOManager.cpp \
    DecisionTreeIOManager.cpp \
    Editor.cpp \
    IOManager.cpp \
    MainWindow.cpp

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
    StateLink.h \
    FiniteStateMachineIOManager.h \
    rapidxml.hpp \
    DecisionTreeIOManager.h \
    Editor.h \
    IOManager.h \
    MainWindow.h

FORMS    += mainwindow.ui
