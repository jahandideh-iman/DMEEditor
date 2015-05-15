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

class Application : public QMainWindow
{
    Q_OBJECT

    typedef QPair<IOManager *, std::function<Editor*()>> IOEditorPair;

public:
    explicit Application(QWidget *parent = 0);
    ~Application();

    static Application *Get();
    static PropertyPanel* GetPropertyPanel();

    Editor *GetEditor();

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
    static Application * app;
};

#endif // MAINWINDOW_H
