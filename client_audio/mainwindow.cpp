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
//    connect(ui->horizontalSlider_sound, SIGNAL(valueChanged(int)), this, SLOT(sl_volume(int)));
    connect(ui->horizontalSlider_sound, SIGNAL(sliderPressed()), this, SLOT(slider_sound_pressed()));
    connect(ui->horizontalSlider_sound, SIGNAL(sliderReleased()), this, SLOT(slider_sound_released()));
    //mute
    connect(ui->pushButton_mute, SIGNAL(mute()), this, SLOT(sl_mute()));

    //musicbar
    // is set when gets initial info
    slider_is_pressed = false;
    sound_pressed = false;
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
    connect(ui->pushButton_pirate, SIGNAL(pressed()),this,SLOT(sl_lang_pirate()));

connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(sl_song(QTreeWidgetItem *, int)));
}
void MainWindow::setDisplay_timer()
{
    int t = time_value->second() + time_value->minute()*60;
    t++; // = std::min(t+1, duration);
    if (t<=duration)
    time_value->setHMS(0,time_value->addSecs(1).minute(),time_value->addSecs(1).second());
    ui->lcdNumber_time->display(this->time_value->toString("mm:ss"));

    if (!slider_is_pressed)
    ui->horizontalSlider_song->setValue(std::min(t, duration));
    song_timer->start(second);
}
void MainWindow::slider_sound_pressed()
{
    sound_pressed = true;
}

void MainWindow::slider_sound_released()
{

    sound_pressed = false;
    int vol = ui->horizontalSlider_sound->value();
    QVariantMap params;
    params.insert("volume", vol);
    emit signalToClient(kSignalVolume, params);
    qDebug("in sl_volume");
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
void MainWindow::sl_stop()
{
    QVariantMap p;
    emit signalToClient(kSignalStop, p);
}
void MainWindow::sl_next()
{
    QVariantMap p;
    emit signalToClient(kSignalNext, p);
    //send socket next
}

void MainWindow::sl_ff()
{
    QVariantMap p;
    emit signalToClient(kSignalFast, p);
    //send socket next
}

void MainWindow::sl_endff()
{
    QVariantMap p;
    emit signalToClient(kSignalEndFast, p);
    //send socket next
}

void MainWindow::sl_back()
{
    QVariantMap p;
    emit signalToClient(kSignalBack, p);
}
void MainWindow::sl_fb()
{
    QVariantMap p;
    emit signalToClient(kSignalFastBack, p);
    //send socket next
}
void MainWindow::sl_endfb()
{
    QVariantMap p;
    emit signalToClient(kSignalEndFastBack, p);
    //send socket next
}




void MainWindow::sl_mute()
{
    QVariantMap p;
    emit signalToClient(kSignalMute, p);
//    QPaintEvent se fait à la reception
}
void MainWindow::sl_lang_fra()
{
    QVariantMap p;
    p["lang"]="fra";
    emit signalToClient(kSignalLang, p);
}
void MainWindow::sl_lang_ger()
{
    QVariantMap p;
    p["lang"]="ger";
    emit signalToClient(kSignalLang, p);
}
void MainWindow::sl_lang_eng()
{
    QVariantMap p;
    p["lang"]="eng";
    emit signalToClient(kSignalLang, p);
}

void MainWindow::sl_lang_pirate(){
    QVariantMap p;
    p["lang"] = "pir";
    emit signalToClient(kSignalLang,p);
}

void MainWindow::sl_song(QTreeWidgetItem *item, int col)
{

    QVariantMap song;
    QString test;
    qDebug() << "pressed a song or list";
    if(item->childCount() == 0 && item->parent() )
    {
        test = item->parent()->text(0) +"/"+item->text(0);
        song["song_name"]=test ;
    }
    else
        song["song_name"]=(item->text(0));

    emit signalToClient(kSignalSong, song);
}



void MainWindow::messageFromClient(signalType sig, QVariantMap params)
{
    int t, vol;
    bool mute;
    QString tree;
    QString song_name;
    switch(sig)
    {
     case kSignalPlay:
        pause_ms = params["pause_ms"].toInt();
        song_timer->start(pause_ms);
            break;
     case kSignalPause:
        song_timer->stop();
            break;
     case kSignalInfo:
        qDebug("Setting up UI");
        //song_name
        song_name = params["song_name"].toString();
        ui->lineEdit->setText(song_name);
        //duration
        duration = (params["duration"]).toLongLong();
        ui->horizontalSlider_song->setMaximum(duration);
        time_duration->setHMS(0,0,0,0);
        time_duration->setHMS(0,time_duration->addSecs(duration).minute(),time_duration->addSecs(duration).second());
        ui->lcdNumber_length->display(time_duration->toString("mm:ss"));
        //time
        t = params["time"].toInt();
        ui->horizontalSlider_song->setValue(t);
        time_value->setHMS(0,0,0,0);
        time_value->setHMS( 0,time_value->addSecs(t).minute(),this->time_value->addSecs(t).second());
        ui->lcdNumber_time->display(time_value->toString("mm:ss"));

        //volume
        vol = params["volume"].toLongLong();
        if (!sound_pressed) ui->horizontalSlider_sound->setValue(vol);
        //mute
        mute = params["mute"].toBool();
        ui->pushButton_mute->set_muted(mute);
        ui->pushButton_mute->repaint();
//        if (mute) ui->pushButton_mute->setStyleSheet("background-color: red;");
        //playing
        pause_ms = params["ms"].toLongLong();
        if (params["play"].toBool()) song_timer->start(pause_ms);
            break;
     case kSignalEvent:
        qDebug("Setting up Event");
        //song_name
        song_name = params["song_name"].toString();
        ui->lineEdit->setText(song_name);
        //duration
        duration = (params["duration"]).toLongLong();
        ui->horizontalSlider_song->setMaximum(duration);
        time_duration->setHMS(0,0,0,0);
        time_duration->setHMS(0,time_duration->addSecs(duration).minute(),time_duration->addSecs(duration).second());
        ui->lcdNumber_length->display(time_duration->toString("mm:ss"));
//        //time
//        t = params["time"].toLongLong();
//        ui->horizontalSlider_song->setValue(t);
//        time_value->setHMS(0,0,0,0);
//        time_value->setHMS( 0,time_value->addSecs(t).minute(),this->time_value->addSecs(t).second());
//        ui->lcdNumber_time->display(time_value->toString("mm:ss"));

        //volume
        vol = params["volume"].toLongLong();
        ui->horizontalSlider_sound->setValue(vol);
        //mute
        mute = params["mute"].toBool();
        if (mute) ui->pushButton_mute->setStyleSheet("background-color: red;");
        //playing
//        pause_ms = params["ms"].toLongLong();
        if (params["play"].toBool()) song_timer->start(pause_ms);
            break;
     case kSignalVolume:
        vol = params["volume"].toLongLong();
        if (!sound_pressed) ui->horizontalSlider_sound->setValue(vol);
            break;
     case kSignalTime:
        t = params["time_change"].toInt();
        qDebug() << "reading new time =" << t;
        time_value->setHMS(0,0,0,0);
        time_value->setHMS(0,time_value->addSecs(t).minute(), time_value->addSecs(t).second());
        ui->lcdNumber_time->display(this->time_value->toString("mm:ss"));
        ui->horizontalSlider_song->setValue(t);
//        song_timer->stop();
//        song_timer->start(1000);
            break;
     case kSignalTree:
        tree = params["data"].toString();
        load_tree_from_string(tree);
            break;
     case kSignalStop:
        //SET text to white
        //stop timers
        //set lcd to 0
        //set song_bar to 0
            break;
        case kSignalNext:
        //We should get info about next song = nothing to do
            break;
        case kSignalFast:
        //We're going twice as fast
        second = 500;
        pause_ms/=2;
            break;
        case kSignalEndFast:
        second = 1000;
        pause_ms *= 2;
        
            break;
        case kSignalBack:
        //receive info
        //this will reset timer to 0
            break;
        case kSignalFastBack:
        //????
        //second = 500;
        //pause_ms = (1000-pause_ms)/2;
        //play_direction = false ??
            break;
        case kSignalEndFastBack:
        //????
        //second = 1000;
        //pause_ms = (500-pause_ms)*2;
        //play_direction = true ??
            break;
        case kSignalSong:
            //INfo
            break;
        case kSignalList:
            break;
        case kSignalLang:{
            QString language = params["lang"].toString();
            if(language == "fra"){
                ui->pushButton_english->setText("ANG");
                ui->pushButton_german->setText("ALL");
                ui->pushButton_french->setText("FRA");
                ui->pushButton_pirate->setText("PIR");
                this->setWindowTitle("Lecteur Audio");
            } else if (language == "eng"){
                ui->pushButton_english->setText("ENG");
                ui->pushButton_german->setText("GER");
                ui->pushButton_french->setText("FRE");
                ui->pushButton_pirate->setText("PIR");
                this->setWindowTitle("Audio Player");
            } else if (language == "ger"){
                ui->pushButton_english->setText("ENG");
                ui->pushButton_german->setText("DEU");
                ui->pushButton_french->setText("FRA");
                ui->pushButton_pirate->setText("PIR");
                this->setWindowTitle("Audio-Player");
            } else if (language == "pir"){
                ui->pushButton_english->setText("ARRR");
                ui->pushButton_german->setText("ARRRRR");
                ui->pushButton_french->setText("ARRR");
                ui->pushButton_pirate->setText("PIR");
                this->setWindowTitle("ARRRRRRRRRRRRRRR");
            }
            break;
        }
        case kSignalMute:
            //QPAINTEVENT
            ui->pushButton_mute->set_muted(! ui->pushButton_mute->get_muted());
            ui->pushButton_mute->repaint();

            break;
        default:
            qDebug() << "not yet implemented";
        break;
    }



}

void MainWindow::load_children_from_string(QTextStream* in, QTreeWidgetItem* parent)
{
              QTreeWidgetItem *item = new QTreeWidgetItem();
    while (!in->atEnd())
       {
          QString line = in->readLine();

//          QTreeWidgetItem *item = new QTreeWidgetItem();
          if (line == "dir")
          {
               load_children_from_string(in, item);
          }
          else if (line == "end_dir")
          {
              break;
          }
          else
          {
              item = new QTreeWidgetItem();
              item->setText(0,line);
          }
          parent->addChild(item);
       }
}

void MainWindow::load_tree_from_string(QString tree)
{
    qDebug() << "Trying to load tree";
    QFile file(TREE_FILE);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << tree;
    file.close();

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    ui->treeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem();

    while (!in.atEnd())
       {
          QString line = in.readLine();

          if (line == "dir")
          {
              load_children_from_string(&in, item);

          }
          else
          {
              item = new QTreeWidgetItem();
              item->setText(0,line);
          }
          ui->treeWidget->addTopLevelItem(item);
       }
}


void MainWindow::closeEvent()
{
    QVariantMap p;
    emit signalToClient(kSignalQuit, p);
    delete ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}
