#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    this->s_test = new(server);
    ui->setupUi(this);
   connect(ui->butto_serv, SIGNAL(pressed()), this, SLOT(send_pressed()));
}

void MainWindow::send_pressed()
{
    emit signal_on();
}

MainWindow::~MainWindow()
{
    delete ui;
}
