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
    time_value = new QTime(0,0,0,0);
    time_duration = new QTime(0,0,0,0);
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
    // is set when gets initial info
    slider_is_pressed = false;
    ui->horizontalSlider_song->setPageStep(100);
    connect(ui->horizontalSlider_song, SIGNAL(sliderPressed()), this, SLOT(slider_song_pressed()));
    connect(ui->horizontalSlider_song, SIGNAL(sliderReleased()), this, SLOT(slider_song_released()));

    ui->lcdNumber_time->display(time_value->toString("mm:ss"));
    QObject::connect(song_timer,SIGNAL(timeout()),this,SLOT(setDisplay_timer()));
//    song_timer->start(1000);

    //language
    connect(ui->pushButton_french, SIGNAL(pressed()), this, SLOT(sl_lang_fra()));
    connect(ui->pushButton_english, SIGNAL(pressed()), this, SLOT(sl_lang_eng()));
    connect(ui->pushButton_german, SIGNAL(pressed()), this, SLOT(sl_lang_ger()));


}
void MainWindow::setDisplay_timer()
{
    time_value->setHMS(0,time_value->addSecs(1).minute(),time_value->addSecs(1).second());
    ui->lcdNumber_time->display(this->time_value->toString("mm:ss"));
    int t = time_value->second() + time_value->minute()*60;
    t++;
    if (!slider_is_pressed)
    ui->horizontalSlider_song->setValue(t);
    song_timer->start(1000);
}

void MainWindow::slider_song_pressed()
{
    slider_is_pressed = true;
}

void MainWindow::slider_song_released()
{
    slider_is_pressed = false;
    //Send_signal
    int pos = ui->horizontalSlider_song->value();
    QVariantMap p;
    p.insert("time_change", pos);
    time_value->setHMS(0,0,0,0);
    time_value->setHMS(0,time_value->addSecs(pos).minute(), time_value->addSecs(pos).second());
    ui->lcdNumber_time->display(this->time_value->toString("mm:ss"));
    emit signalToClient(kSignalTime, p);
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
        ui->horizontalSlider_song->setMaximum(duration);
        time_duration->setHMS(0,time_duration->addSecs(duration).minute(),time_duration->addSecs(duration).second());
        ui->lcdNumber_length->display(time_duration->toString("mm:ss"));
        //time
        int t = params["time"].toLongLong();
        ui->horizontalSlider_song->setValue(t);
        time_value->setHMS( 0,time_value->addSecs(t).minute(),this->time_value->addSecs(t).second());
        ui->lcdNumber_time->display(time_value->toString("mm:ss"));

        //volume
        int vol = params["volume"].toLongLong();
        ui->horizontalSlider_sound->setValue(vol);
        //mute
        bool mute = params["mute"].toBool();
        if (mute) ui->pushButton_mute->setStyleSheet("background-color: red;");
        //playing
        pause_ms = params["ms"].toLongLong();
        if (params["play"].toBool()) song_timer->start(pause_ms);
    }
    if (sig == kSignalPlay)
    {
        pause_ms = params["pause_ms"].toInt();
        song_timer->start(pause_ms);
    }
    if (sig == kSignalPause)
    {
//        pause_ms = song_timer->remainingTime();
        song_timer->stop();
    }
    if (sig == kSignalTime)
    {
        int t = params["time_change"].toInt();
        time_value->setHMS(0,0,0,0);
        time_value->setHMS(0,time_value->addSecs(t).minute(), time_value->addSecs(t).second());
        song_timer->stop();
        song_timer->start(1000);
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
