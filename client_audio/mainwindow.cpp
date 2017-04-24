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
//    this->c_test = new(client);
    song_timer = new QTimer();
    time_value = new QTime();
    pause_ms = 1000;
    ui->setupUi(this);

    //Create socket
    //Connect to server
    //Receive info from server


    //Connect buttons
    //play
    connect(ui->pushButton_play, SIGNAL(pressed()), this, SLOT(sl_play()));
    //pause
    connect(ui->pushButton_pause, SIGNAL(pressed()), this, SLOT(sl_pause()));



    //stop
    connect(ui->pushButton_stop, SIGNAL(pressed()), this, SLOT(sl_stop()));
    //next
    connect(ui->pushButton_next, SIGNAL(pressed()), this, SLOT(sl_next()));
    //back
    connect(ui->pushButton_back, SIGNAL(pressed()), this, SLOT(sl_back()));

    //soundbar
    ui->horizontalSlider_sound->setValue(100);
    connect(ui->horizontalSlider_sound, SIGNAL(valueChanged(int)), this, SLOT(sl_volume(int)));
    //mute
    connect(ui->pushButton_mute, SIGNAL(pressed()), this, SLOT(sl_mute()));

    //musicbar
    ui->horizontalSlider_song->setMinimum(0);
    ui->horizontalSlider_song->setMaximum(100);
    ui->lcdNumber_length->display(100);
    ui->horizontalSlider_song->setValue(25);

    time_value = new QTime(0,0,0,0);
    ui->lcdNumber_time->display(time_value->toString("mm:ss"));
    QObject::connect(song_timer,SIGNAL(timeout()),this,SLOT(setDisplay_timer()));
    song_timer->start(1000);

    //language
    connect(ui->pushButton_french, SIGNAL(pressed()), this, SLOT(sl_lang_fra()));
    connect(ui->pushButton_english, SIGNAL(pressed()), this, SLOT(sl_lang_eng()));
    connect(ui->pushButton_german, SIGNAL(pressed()), this, SLOT(sl_lang_ger()));


}
void MainWindow::setDisplay_timer()
{
    time_value->setHMS(0,time_value->addSecs(1).minute(),this->time_value->addSecs(1).second());
    ui->lcdNumber_time->display(this->time_value->toString("mm:ss"));
    song_timer->start(1000);
}

void MainWindow::sl_play()
{
    QVariantMap params;
    emit signalToClient(kSignalPlay, params);
}
void MainWindow::sl_pause()
{
    QVariantMap params;
    emit signalToClient(kSignalPause, params);
}
void MainWindow::sl_volume(int vol)
{
    QVariantMap params;
    params.insert("volume", vol);
    emit signalToClient(kSignalVolume, params);
    qDebug("in sl_volume");
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



void MainWindow::messageFromClient(signalType sig, QVariantMap params)
{
    if (sig == kSignalInfo)
    {
        qDebug("Setting up UI");
        //song_name
        QString song_name = params["song_name"].toString();
        ui->lineEdit->setText(song_name);
        //duration
        int duration = (params["duration"]).toLongLong();
        ui->lcdNumber_length->display(duration);
        //time
        int t = params["time"].toLongLong();
        time_value->setHMS( 0,time_value->addSecs(t).minute(),this->time_value->addSecs(t).second());
        ui->lcdNumber_time->display(time_value->toString("mm:ss"));

        //volume
        int vol = params["volume"].toLongLong();
        ui->horizontalSlider_sound->setValue(vol);
        //mute
        bool mute = params["mute"].toBool();
        if (mute) ui->pushButton_mute->setStyleSheet("background-color: red;");
    }
    if (sig == kSignalPlay)
    {
        song_timer->start(pause_ms);
    }
    if (sig == kSignalPause)
    {
        pause_ms = song_timer->remainingTime();
        song_timer->stop();
    }

}


void MainWindow::closeEvent()
{
    delete ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}
