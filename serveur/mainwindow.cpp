#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString program = "mpv";
    QStringList arguments;
    arguments << "/home/cyrille/Music/Bangles - Eternal Flame.mp3" << "--input-ipc-server=/tmp/mpvsocket";
    myProcess = new QProcess(this);
    myProcess->start(program, arguments);
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
    myProcess->kill();
    delete myProcess;
    delete ui;
}
