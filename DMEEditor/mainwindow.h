#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "DecisionTreeEditor.h"
#include "FiniteStateMachineEditor.h"
#include "PropertyPanel.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static PropertyPanel* GetPropertyPanel();

public slots:
    void CreateNewDecisionTreeEditor();
    void CreateNewFiniteStateMachine();
    void SaveToFile();
    void OpenFile();

private:
    Ui::MainWindow *ui;

    DecisionTreeEditor* editor = nullptr;

    FiniteStateMachineEditor *FSMEditor = nullptr;


};

#endif // MAINWINDOW_H
