#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StringProperty.h"


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
    propertyPanel = new PropertyPanel(this);
    editor = new DecisionTreeEditor(propertyPanel);


    ui->viewLayout->addWidget(editor->GetView(),0,0,3,1);
    ui->viewLayout->addWidget(propertyPanel,0,3,1,1, Qt::AlignLeft);

}
