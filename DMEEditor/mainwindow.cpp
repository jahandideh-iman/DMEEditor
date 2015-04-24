#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StringProperty.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionNew_Decision_Tree,SIGNAL(triggered()),this,SLOT(CreateNewDecisionTreeEditor()));
    QObject::connect(ui->actionNew_Finite_State_Machine,SIGNAL(triggered()),this, SLOT(CreateNewFiniteStateMachine()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(SaveToFile()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(OpenFile()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

PropertyPanel *MainWindow::GetPropertyPanel()
{
    static PropertyPanel *propertyPanel = new PropertyPanel();
    return propertyPanel;
}

void MainWindow::CreateNewDecisionTreeEditor()
{
    editor = new DecisionTreeEditor();


    ui->viewLayout->addWidget(editor->GetView(),0,0,3,1);
    ui->viewLayout->addWidget(GetPropertyPanel(),0,3,1,1, Qt::AlignLeft);

}

void MainWindow::CreateNewFiniteStateMachine()
{
    FSMEditor = new FiniteStateMachineEditor();

    ui->viewLayout->addWidget(FSMEditor->GetView(),0,0,3,1);
    ui->viewLayout->addWidget(GetPropertyPanel(),0,3,1,1, Qt::AlignLeft);
}

void MainWindow::SaveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/jana/untitled.txt",
                               tr("Text (*.txt)"));
    if(editor != nullptr)
        editor->SaveToFile(fileName);
    else
        FSMEditor->SaveToFile(fileName);

}

void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",
                               tr("Text (*.txt)"));

    if(editor != nullptr)
        editor->OpenFromFile(fileName);
    else
        FSMEditor->OpenFromFile(fileName);

}
