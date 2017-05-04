/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */

#include "automate.h"

automate::automate(QObject *parent) : QObject(parent)
{
    startup = true;
//    playing = true;
    muted = false;
    stopped = false;
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
    stop=new QState(machine);
//    stop=new QState(machine);

    // Rajouter son et niveau sonore et mute

    //Transitions sur signaux
    play->addTransition(this, SIGNAL(signalPause()), pause);
    play->addTransition(this, SIGNAL(signalStop()), stop);
    pause->addTransition(this, SIGNAL(signalPlay()), play);
    pause->addTransition(this, SIGNAL(signalStop()), stop);
    stop->addTransition(this, SIGNAL(signalPlay()), play);


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
        stopped = false;
        emit signalMachine(kSignalPlay, p);
        qDebug() << "QState Play";
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
//        if (startup)
//        {
//            startup = false;
//            emit signalMachine(kSignalStartup, p);

//        }
    });
    QObject::connect(stop, &QState::entered, [this]()
    {
        stopped = true;
        song_time->setHMS(0, 0, 0, 0);
        songTimer->stop();
        pause_ms = 1000;
        playing = false;
        song_name = "Please Select Music or List";
        song_duration = 0;
//        song_time = 0;
        qDebug() << "Stopped now sending stop info";
        send_stop_info();
    });
    machine->setInitialState(pause);
    machine->start();
//    load_preferences();
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
      if (!stopped)
      setPlay();
//      qDebug("setplay");
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
      song_name = params["song_name"].toString();
      song_duration = params["duration"].toInt();

            send_info();
            qDebug() << "machine send info";
      break;
  case kSignalStartup:
//      song_name = params["song_name"].toString();
//      song_duration = params["duration"].toInt();
        qDebug() << "received kSigStart with s_d = " << song_duration;
        send_info();
        emit signalMachine(kSignalStartup, params);
      break;
  case kSignalTime:
      qDebug() << "machine received time sig";

        t = params["time_change"].toInt();
        qDebug() << "time = " << t;
        song_time->setHMS(0, 0, 0, 0);
        if (t)
        song_time->setHMS(0,song_time->addSecs(t).minute(), song_time->addSecs(t).second());
//        qDebug() << "cant setHMS if t = " << t;
//        songTimer->stop();
//        songTimer->start(1000);
        qDebug() << "received kSigTime with t_c = " << t;
        emit signalMachine(kSignalTime, params);
      break;
  case kSignalSong:
//      song_time->setHMS(0, 0, 0, 0);
//      song_time->setHMS(0,song_time->addSecs(t).minute(), song_time->addSecs(t).second());
//      songTimer->stop();
//      songTimer->start(1000);
      qDebug() << "received new song in machine";
      stopped = false;
      emit signalMachine(kSignalSong, params);
//      setPlay();
//      send_info();
      break;
  case kSignalEvent:
      song_name = params["song_name"].toString();
      song_duration = params["duration"].toInt();
        send_event();
      break;
  case kSignalStop:
      pause_ms = 1000;
      qDebug() << "why not zoidberg";
      setStop();
//      emit signalStop();
      break;
  case kSignalNext:
      emit signalMachine(kSignalNext, params);
      break;
  case kSignalBack:
      emit signalMachine(kSignalBack, params);
      break;
  case kSignalFast:
      emit signalMachine(kSignalFast, params);
      break;
  case kSignalEndFast:
      emit signalMachine(kSignalEndFast, params);
      break;
  case kSignalMute:
      if (muted) muted = false;
      else muted = true;
      params["muted"]=muted;
      emit signalMachine(kSignalMute, params);
      break;
  case kSignalSave:
      save_preferences();
      break;
  case kSignalSetup:
      qDebug() << "asking for setup ";
      load_preferences();
      break;
  case kSignalLang:
        language = params["lang"].toString();
      emit signalMachine(kSignalLang, params);
      break;
  default:

      break;
  }
}

void automate::send_info(){
    QVariantMap jsonObject;
    jsonObject.insert("signal",kSignalInfo);
    jsonObject.insert("song_name",song_name);
    jsonObject.insert("duration",song_duration);
    qDebug() << "before getting time in info";
    int s = 0;
    qDebug() << song_time->second();
        s = song_time->second() + song_time->minute()*60;
    qDebug() << "after getting time in info";
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

void automate::send_stop_info(){
    QVariantMap jsonObject;
    jsonObject.insert("signal",kSignalInfo);
    jsonObject.insert("song_name",song_name);
    jsonObject.insert("duration",song_duration);
    qDebug() << "before getting time in stopinfo";
    int s = 0;
    qDebug() << "after getting time in stopinfo";
    jsonObject.insert("time", s);
    int ms = songTimer->remainingTime();
    if (ms == -1) ms = pause_ms;
    qDebug() << "remain = " << ms;
    jsonObject.insert("ms", ms);
    jsonObject.insert("volume",volume);
    jsonObject.insert("mute",muted);
    jsonObject.insert("play",playing);
    emit signalMachine(kSignalStop, jsonObject);
}

void automate::send_event(){
    QVariantMap jsonObject;
    jsonObject.insert("signal",kSignalEvent);
    jsonObject.insert("song_name",song_name);
    jsonObject.insert("duration",song_duration);
    jsonObject.insert("volume",volume);
    jsonObject.insert("mute",muted);
    jsonObject.insert("play",playing);
    emit signalMachine(kSignalEvent, jsonObject);
}

void automate::setPause(){

  emit signalPause();
}

void automate::setPlay(){

  emit signalPlay();
}

void automate::setStop()
{
    emit signalStop();
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

void automate::save_preferences()
{
    QFile file("./preferences.txt");
    qDebug("Opened prefs to save prefs" );
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    //Save preferences
    //Song_name
    out << song_name << "\n";
    //muted
    out << muted<< "\n";
    //playing
    out << playing<< "\n";
    //volume
    out << volume<< "\n";
    //time-pos
    int t = song_time->second() + song_time->minute()*60;
    out << t<< "\n";
    //duration
    out << song_duration<< "\n";
    file.close();
    qDebug() << "dont have time";
}

void automate::load_preferences()
{
    QFile file("./preferences.txt");
    int t;
    qDebug("Opened prefs to load prefs" );
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while(!in.atEnd())
    {
        qDebug() << "reading";
        song_name = in.readLine();

        if (song_name == "0") break;
        muted = in.readLine().toInt();
        playing = in.readLine().toInt();
        volume = in.readLine().toInt();
        t = in.readLine().toInt();
        song_time->setHMS(0,song_time->addSecs(t).minute(), song_time->addSecs(t).second());
        song_duration = in.readLine().toInt();
    }
    file.close();
    QVariantMap params;
    params["song_name"] = song_name;
    params["muted"] = muted;
    params["playing"] = playing;
    params["time-pos"] = t;
    params["duration"] = song_duration;
    if (song_name != "")
    {
        qDebug() << "sending setup message" << song_name;
        emit signalMachine(kSignalSetup, params);
        qDebug() << "sent setup message";
    }
    qDebug() << "finished loading prefs";
}







