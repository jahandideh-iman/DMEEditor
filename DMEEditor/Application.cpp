#include "Application.h"
#include "ui_mainwindow.h"
#include "DecisionTreeEditor.h"
#include "DecisionTreeIOManager.h"
#include "FiniteStateMachineEditor.h"
#include "FiniteStateMachineIOManager.h"
#include "BehaviorTreeEditor.h"
#include "BehaviorTreeIOManager.h"
#include <QFileDialog>

PropertyPanel* Application::propertyPanel = nullptr;
Application* Application::app = nullptr;

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigUIEvents();
    ConfigIOManagerEditorPairs();

    app = this;
}

Application::~Application()
{
    DestoryEditor();
    delete ui;
    delete propertyPanel;
}

Application *Application::Get()
{
    return app;
}

void Application::ConfigUIEvents()
{
    QObject::connect(ui->actionNew_Decision_Tree,SIGNAL(triggered()),this,SLOT(CreateNewDecisionTreeEditor()));
    QObject::connect(ui->actionNew_Finite_State_Machine,SIGNAL(triggered()),this, SLOT(CreateNewFiniteStateMachine()));
    QObject::connect(ui->actionNew_Behavior_Tree,SIGNAL(triggered()),this, SLOT(CreateNewBehaviorTree()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(SaveToFile()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(OpenFile()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
}

void Application::ConfigIOManagerEditorPairs()
{
    ioEditorPairs.push_back(IOEditorPair(new DecisionTreeIOManager(), []()->Editor*{return new DecisionTreeEditor();}));
    ioEditorPairs.push_back(IOEditorPair(new FiniteStateMachineIOManager(), []()->Editor*{return new FiniteStateMachineEditor();}));
    ioEditorPairs.push_back(IOEditorPair(new BehaviorTreeIOManager(), []()->Editor*{return new BehaviorTreeEditor();}));
}

PropertyPanel *Application::GetPropertyPanel()
{
    if(propertyPanel == nullptr)
        propertyPanel = new PropertyPanel();
    return propertyPanel;
}

Editor *Application::GetEditor()
{
    return editor;
}

void Application::CreateNewDecisionTreeEditor()
{
    SetEditor(new DecisionTreeEditor());
}

void Application::CreateNewFiniteStateMachine()
{
    SetEditor(new FiniteStateMachineEditor());
}

void Application::CreateNewBehaviorTree()
{
    SetEditor(new BehaviorTreeEditor());
}

void Application::SetEditor(Editor *editor)
{
    DestoryEditor();

    this->editor = editor;
    ui->viewLayout->addWidget(editor->GetView(),0,0,3,1);
    ui->viewLayout->addWidget(GetPropertyPanel(),0,3,1,1, Qt::AlignLeft);
}

void Application::DestoryEditor()
{
    if(editor == nullptr)
        return;

    ui->viewLayout->removeWidget(editor->GetView());
    delete editor;
}

void Application::SaveToFile()
{
    if(editor == nullptr)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "untitled.txt",tr("Text (*.txt)"));
    for(auto ioEditorPair : ioEditorPairs)
        if (ioEditorPair.first->IsCompatibleWith(editor))
            ioEditorPair.first->SaveToFile(fileName,editor);
}

void Application::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",
                               tr("Text (*.txt)"));
    QString fileType = IOManager::ReadFileType(fileName);
    for(auto ioEditorPair : ioEditorPairs)
        if (ioEditorPair.first->IsFileTypeValid(fileType))
        {
            SetEditor(ioEditorPair.second());
            ioEditorPair.first->ReadFromFile(fileName,editor);
        }
}
