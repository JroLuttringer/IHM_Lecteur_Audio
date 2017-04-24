#include "automate.h"

automate::automate(QObject *parent) : QObject(parent)
{
    muted = false;
    volume = 50;
    //Timer representant la chanson en lecture
    songTimer =new QTimer(this);
    songTimer->setSingleShot(true);
    songTimer->setTimerType(Qt::PreciseTimer);

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

    //Transition sur le meme etat mais on doit changer de chanson et restart le timer
//    play->addTransition(songTimer, SIGNAL(timeout()), play);

    //On prepare les actions sur les Timers donc la chanson
    QObject::connect(play, SIGNAL(entered()), songTimer, SLOT(start()));
    QObject::connect(pause, SIGNAL(entered()), songTimer, SLOT(stop()));
//    QObject::connect(stop, SIGNAL(entered()), songTimer, SLOT(stop()));



    //when stop reset timer to 0 also

    setupMessages();
}

void automate::setupMessages()
{
    //message d'initialisation de la sauvegarde



    //connect les messages à destination du serveur
    QObject::connect(play, &QState::entered, [this]()
    {
        QVariantMap params; //parametres bidons
        params["1"]=QVariant(true);
        params["2"]=QVariant(true);
        params["bac"]=QVariant(true);
        emit signalMachine(kSignalPlay, params);
    });
    QObject::connect(pause, &QState::entered, [this]()
    {
        QVariantMap params; //parametres bidons
        params["1"]=QVariant(true);
        params["2"]=QVariant(true);
        params["bac"]=QVariant(true);
        emit signalMachine(kSignalPause, params);
    });
    machine->setInitialState(pause);
    machine->start();
}

void automate::message(signalType sig, QVariantMap params) {
  switch(sig){
  case kSignalPlay:
      setPlay();
      qDebug("setplay");
      break;
  case kSignalPause:
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
  default:
      break;
  }
}

void automate::send_info(){
    QVariantMap params;
    emit signalMachine(kSignalInfo, params);
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
