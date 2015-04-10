#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "DecisionTreeEditor.h"
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

public slots:
    void CreateNewDecisionTreeEditor();
    void SaveToFile();

private:
    Ui::MainWindow *ui;

    DecisionTreeEditor* editor = nullptr;

    PropertyPanel* propertyPanel = nullptr;


};

#endif // MAINWINDOW_H
