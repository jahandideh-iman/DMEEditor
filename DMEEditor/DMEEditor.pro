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
        mainwindow.cpp \
    UndeterminedDecisionTreeNode.cpp \
    DecisionTreeNode.cpp \
    DecisionTreeEditor.cpp \
    DecisionNode.cpp \
    ActionNode.cpp

HEADERS  += mainwindow.h \
    UndeterminedDecisionTreeNode.h \
    DecisionTreeNode.h \
    DecisionTreeEditor.h \
    DecisionNode.h \
    ActionNode.h

FORMS    += mainwindow.ui
