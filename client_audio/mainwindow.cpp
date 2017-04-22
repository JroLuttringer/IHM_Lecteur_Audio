/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */

#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->c_test = new(client);
    ui->setupUi(this);

    //Create socket
    //Connect to server
    //Receive info from server


    //Connect buttons
    //play
    connect(ui->pushButton_play, SIGNAL(pressed()), this->c_test, SLOT(sl_play()));
    //pause
    connect(ui->pushButton_pause, SIGNAL(pressed()), this->c_test, SLOT(sl_pause()));



    //stop
    connect(ui->pushButton_stop, SIGNAL(pressed()), this, SLOT(sl_stop()));
    //next
    connect(ui->pushButton_next, SIGNAL(pressed()), this, SLOT(sl_next()));
    //back
    connect(ui->pushButton_back, SIGNAL(pressed()), this, SLOT(sl_back()));

    //soundbar
    //mute
    connect(ui->pushButton_mute, SIGNAL(pressed()), this, SLOT(sl_mute()));

    //musicbar
    ui->horizontalSlider_song->setMinimum(0);
    ui->horizontalSlider_song->setMaximum(100);
    ui->lcdNumber_length->display(100);
    ui->horizontalSlider_song->setValue(25);
    ui->lcdNumber_time->display(25);

    //language
    connect(ui->pushButton_french, SIGNAL(pressed()), this, SLOT(sl_lang_fra()));
    connect(ui->pushButton_english, SIGNAL(pressed()), this, SLOT(sl_lang_eng()));
    connect(ui->pushButton_german, SIGNAL(pressed()), this, SLOT(sl_lang_ger()));

}


void MainWindow::sl_stop()
{
    //send socket stop
}
void MainWindow::sl_next()
{
    //send socket next
}
void MainWindow::sl_back()
{
    //send socket back
}
void MainWindow::sl_mute()
{
    //send socket mute
}
void MainWindow::sl_lang_fra()
{
    //send socket fra
}
void MainWindow::sl_lang_ger()
{
    //send socket ger
}
void MainWindow::sl_lang_eng()
{
    //send socket eng
}

void MainWindow::closeEvent()
{
    delete this->c_test;
    delete ui;
}

MainWindow::~MainWindow()
{
    delete this->c_test;
    delete ui;
}
