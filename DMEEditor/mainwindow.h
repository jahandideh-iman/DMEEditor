#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PropertyPanel.h"
#include "Editor.h"
#include "IOManager.h"
#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    typedef QPair<IOManager *, std::function<Editor*()>> IOEditorPair;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static PropertyPanel* GetPropertyPanel();

public slots:
    void CreateNewDecisionTreeEditor();
    void CreateNewFiniteStateMachine();
    void CreateNewBehaviorTree();
    void SaveToFile();
    void OpenFile();

private:
    void ConfigUIEvents();
    void ConfigIOManagerEditorPairs();

    void SetEditor(Editor *editor);
    void DestoryEditor();

private:
    Ui::MainWindow *ui;

    Editor* editor = nullptr;

    QVector<IOEditorPair> ioEditorPairs;

    static PropertyPanel *propertyPanel;
};

#endif // MAINWINDOW_H
