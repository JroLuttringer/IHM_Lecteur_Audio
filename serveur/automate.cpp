#include "automate.h"

automate::automate(QObject *parent) : QObject(parent)
{
    startup = true;
//    playing = true;
    muted = false;
    volume = 100;
    //Timer representant la chanson en lecture
    songTimer =new QTimer(this);
    songTimer->setSingleShot(true);
    songTimer->setTimerType(Qt::PreciseTimer);
    QObject::connect(songTimer,SIGNAL(timeout()),this,SLOT(increase_time()));
    song_time = new QTime();
    song_time = new QTime(0,0,0,0);
    pause_ms = 1000;

    // Une machine
    machine =new QStateMachine(this);

    //  Les états "en pause"
    pause=new QState(machine);
    play=new QState(machine);
//    stop=new QState(machine);

    // Rajouter son et niveau sonore et mute

    //Transitions sur signaux
    play->addTransition(this, SIGNAL(signalPause()), pause);
    pause->addTransition(this, SIGNAL(signalPlay()), play);


    setupMessages();
}

void automate::setupMessages()
{
    //message d'initialisation de la sauvegarde



    //connect les messages à destination du serveur
    QObject::connect(play, &QState::entered, [this]()
    {
        playing = true;    //play timer
        songTimer->start(pause_ms);
        QVariantMap p;
        p.insert("pause_ms", pause_ms);
        emit signalMachine(kSignalPlay, p);
    });
    QObject::connect(pause, &QState::entered, [this]()
    {
        playing = false;    //pause timer
        pause_ms = songTimer->remainingTime();
        if (pause_ms == -1) pause_ms = 1000;
        qDebug() << pause_ms;
        songTimer->stop();
        QVariantMap p;
        emit signalMachine(kSignalPause, p);
        if (startup)
        {
            startup = false;
            emit signalMachine(kSignalStartup, p);

        }
    });
    machine->setInitialState(pause);
    machine->start();
//    startup_info();
}

void automate::increase_time()
{
    song_time->setHMS(0,song_time->addSecs(1).minute(),song_time->addSecs(1).second());
    songTimer->start(1000);
    int s = song_time->second() + song_time->minute()*60;
    qDebug() << s;
}

void automate::message(signalType sig, QVariantMap params) {
    int t;
  switch(sig){
  case kSignalPlay:
//      if (playing) break;
      setPlay();
      qDebug("setplay");
      break;
  case kSignalPause:
//      if (!playing) break;
      setPause();
      break;
  case kSignalVolume:
      int vol;
      vol = params["volume"].toLongLong();
      setVolume(vol);
      break;
  case kSignalInfo:
        send_info();
      break;
  case kSignalStartup:
        song_name = params["song_name"].toString();
        song_duration = params["duration"].toInt();
        qDebug() << "received kSigStart with s_d = " << song_duration;
      break;
  case kSignalTime:
        t = params["time_change"].toInt();
        song_time->setHMS(0, 0, 0, 0);
        song_time->setHMS(0,song_time->addSecs(t).minute(), song_time->addSecs(t).second());
        songTimer->stop();
        songTimer->start(1000);
        qDebug() << "received kSigTime with t_c = " << t;
        emit signalMachine(kSignalTime, params);
      break;
  default:

      break;
  }
}

void automate::send_info(){
    QVariantMap jsonObject;
    jsonObject.insert("signal","info");
    jsonObject.insert("song_name",song_name);
    jsonObject.insert("duration",song_duration);
    int s = song_time->second() + song_time->minute()*60;
    jsonObject.insert("time", s);
    int ms = songTimer->remainingTime();
    if (ms == -1) ms = pause_ms;
    qDebug() << "remain = " << ms;
    jsonObject.insert("ms", ms);
    jsonObject.insert("volume",volume);
    jsonObject.insert("mute",muted);
    jsonObject.insert("play",playing);
    emit signalMachine(kSignalInfo, jsonObject);
}

void automate::setPause(){

  emit signalPause();
}

void automate::setPlay(){

  emit signalPlay();
}

void automate::setVolume(int vol)
{
    volume = vol;
    QVariantMap params;
    params.insert("volume", vol);
    emit signalMachine(kSignalVolume, params);
}

//Fonction pour initialiser toutes les valeurs (song_name, duration, muted etc.)

void automate::startup_info()
{
    qDebug("MAchine asking server for startup info");
    QVariantMap params;
    emit signalMachine(kSignalStartup, params);
}









