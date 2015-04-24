#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "DecisionTreeEditor.h"
#include "DecisionTreeIOManager.h"
#include "FiniteStateMachineEditor.h"
#include "FiniteStateMachineIOManager.h"
#include <QFileDialog>

PropertyPanel* MainWindow::propertyPanel = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigUIEvents();
    ConfigIOManagerEditorPairs();
}

MainWindow::~MainWindow()
{
    DestoryEditor();
    delete ui;
    delete propertyPanel;
}

void MainWindow::ConfigUIEvents()
{
    QObject::connect(ui->actionNew_Decision_Tree,SIGNAL(triggered()),this,SLOT(CreateNewDecisionTreeEditor()));
    QObject::connect(ui->actionNew_Finite_State_Machine,SIGNAL(triggered()),this, SLOT(CreateNewFiniteStateMachine()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(SaveToFile()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(OpenFile()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
}

void MainWindow::ConfigIOManagerEditorPairs()
{
    ioEditorPairs.push_back(IOEditorPair(new DecisionTreeIOManager(), []()->Editor*{return new DecisionTreeEditor();}));
    ioEditorPairs.push_back(IOEditorPair(new FiniteStateMachineIOManager(), []()->Editor*{return new FiniteStateMachineEditor();}));
}

PropertyPanel *MainWindow::GetPropertyPanel()
{
    if(propertyPanel == nullptr)
        propertyPanel = new PropertyPanel();
    return propertyPanel;
}

void MainWindow::CreateNewDecisionTreeEditor()
{
    SetEditor(new DecisionTreeEditor());
}

void MainWindow::CreateNewFiniteStateMachine()
{
    SetEditor(new FiniteStateMachineEditor());
}

void MainWindow::SetEditor(Editor *editor)
{
    DestoryEditor();

    this->editor = editor;
    ui->viewLayout->addWidget(editor->GetView(),0,0,3,1);
    ui->viewLayout->addWidget(GetPropertyPanel(),0,3,1,1, Qt::AlignLeft);
}

void MainWindow::DestoryEditor()
{
    if(editor == nullptr)
        return;

    ui->viewLayout->removeWidget(editor->GetView());
    delete editor;
}

void MainWindow::SaveToFile()
{
    if(editor == nullptr)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "untitled.txt",tr("Text (*.txt)"));
    for(auto ioEditorPair : ioEditorPairs)
        if (ioEditorPair.first->IsCompatibleWith(editor))
            ioEditorPair.first->SaveToFile(fileName,editor);
}

void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",
                               tr("Text (*.txt)"));
    for(auto ioEditorPair : ioEditorPairs)
        if (ioEditorPair.first->IsFileValid(fileName))
        {
            SetEditor(ioEditorPair.second());
            ioEditorPair.first->ReadFromFile(fileName,editor);
        }
}
