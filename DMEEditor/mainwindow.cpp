#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionNew_Decision_Tree,SIGNAL(triggered()),this,SLOT(CreateNewDecisionTreeEditor()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateNewDecisionTreeEditor()
{
    editor = new DecisionTreeEditor();

    ui->ViewLayout->addWidget(editor->GetView());
}
