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
    DecisionTreeScene.cpp \
    UnkownDecisionTreeNode.cpp \
    Node.cpp

HEADERS  += mainwindow.h \
    DecisionTreeScene.h \
    UnkownDecisionTreeNode.h \
    Node.h

FORMS    += mainwindow.ui
