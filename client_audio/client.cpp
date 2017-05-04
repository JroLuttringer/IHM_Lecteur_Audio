/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */

#include "client.h"


client::client(QObject *parent) : QObject(parent),
    m_socket(new QLocalSocket(this))
{
    qRegisterMetaType<signalType>("signalType");
    m_running=true;
    m_clientLoopThread=QtConcurrent::run(this, &client::serverMessageLoop);
    m_socket->connectToServer(SERVER_NAME);

    if (m_socket->waitForConnected())
    {
        qDebug("connected");
    }
    else
    { // Non connecté
        qDebug()<<m_socket->errorString();
        m_socket->disconnectFromServer();
    }
    sl_start();
}


void client::serverMessageLoop()
{
    while (m_running)
    {
        QDataStream in(m_socket);
        if (in.atEnd())
        { // Rien dans la file d'attente
            QThread::msleep(100); // On attend 1/10s et on continue
            continue;
        }
        QString str=QString(in.device()->readLine());
        if(str=="") continue; // Evitons les lignes vides.
        qDebug() << qPrintable(str);
        QByteArray a=str.toUtf8();
        QJsonParseError error;
        QJsonDocument jDoc=QJsonDocument::fromJson(a, &error);
        QJsonObject jsonObject=jDoc.object();
        if (!jsonObject.contains("signal"))
        {
            qDebug() << "empty signal, this is a disconnect";
            continue;
        }
        switch(jsonObject["signal"].toInt())
        {
            case kSignalPlay:
            emit signalFromClient(kSignalPlay, jsonObject.toVariantMap());
                break;
            case kSignalPause:
            emit signalFromClient(kSignalPause, jsonObject.toVariantMap());
                break;
            case kSignalInfo:
            qDebug() << a;
            emit signalFromClient(kSignalInfo, jsonObject.toVariantMap());
                break;
            case kSignalEvent:
            qDebug() << a;
            emit signalFromClient(kSignalEvent, jsonObject.toVariantMap());
                break;
            case kSignalVolume:
            emit signalFromClient(kSignalVolume, jsonObject.toVariantMap());
                break;
            case kSignalTime:
            emit signalFromClient(kSignalTime, jsonObject.toVariantMap());
                break;
            case kSignalTree:
            emit signalFromClient(kSignalTree, jsonObject.toVariantMap());
                break;
            case kSignalStop:
            emit signalFromClient(kSignalStop, jsonObject.toVariantMap());
                break;
            case kSignalNext:
            emit signalFromClient(kSignalNext, jsonObject.toVariantMap());
                break;
            case kSignalFast:
            emit signalFromClient(kSignalFast, jsonObject.toVariantMap());
                break;
            case kSignalEndFast:
            emit signalFromClient(kSignalEndFast, jsonObject.toVariantMap());
                break;
            case kSignalBack:
            emit signalFromClient(kSignalBack, jsonObject.toVariantMap());
                break;
            case kSignalFastBack:
            emit signalFromClient(kSignalFastBack, jsonObject.toVariantMap());
                break;
            case kSignalEndFastBack:
            emit signalFromClient(kSignalEndFastBack, jsonObject.toVariantMap());
                break;
            case kSignalSong:
                break;
            case kSignalList:
                break;
            case kSignalLang:
            emit signalFromClient(kSignalLang, jsonObject.toVariantMap());
                break;
            case kSignalMute:
            emit signalFromClient(kSignalMute, jsonObject.toVariantMap());
                break;
            default:
                qDebug() << "not yet implemented";
            break;
        }
    }
}

void client::sl_info()
{
    QJsonObject jsonObject;
    jsonObject["signal"] = kSignalInfo;

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void client::sl_start()
{
    //send socket play
    QJsonObject jsonObject;
//    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
//    request << "play_client";
    jsonObject["signal"] = kSignalStartup;

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void client::sl_play()
{
    //send socket play
    QJsonObject jsonObject;
//    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
//    request << "play_client";
    jsonObject["signal"] = kSignalPlay;

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}
void client::sl_pause()
{
    //send socket pause
    QJsonObject jsonObject;
//    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
//    request << "pause_client";
    jsonObject["signal"] = kSignalPause;

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void client::sl_volume(int vol)
{
    QJsonObject jsonObject;
    jsonObject["signal"] = kSignalVolume;
    jsonObject["volume"] = vol;

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void client::messageFromUI(signalType sig, QVariantMap params) {
    qDebug("received message from UI");

    QJsonObject jsonObject;
    QByteArray bytes;
  switch(sig){
  case kSignalPlay:
        sl_play();
      break;
  case kSignalPause:
        sl_pause();
      break;
  case kSignalVolume:
        int vol;
        vol= params["volume"].toLongLong();
        sl_volume(vol);
      break;
  case kSignalTime:
      jsonObject["signal"] = kSignalTime;
      jsonObject["time_change"] = params["time_change"].toInt();
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalSong:
      jsonObject["signal"] = kSignalSong;
      jsonObject["song_name"] = params["song_name"].toString();
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
//        QThread::sleep(1);
//      sl_info();
      break;
  case kSignalQuit:
      jsonObject["signal"] = kSignalQuit;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      QThread::msleep(1000);
         this->~client();
  break;
  case kSignalStop:
      jsonObject["signal"] = kSignalStop;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalNext:
      jsonObject["signal"] = kSignalNext;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalFast:
      jsonObject["signal"] = kSignalFast;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalEndFast:
      jsonObject["signal"] = kSignalEndFast;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalBack:
      jsonObject["signal"] = kSignalBack;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalFastBack:
      jsonObject["signal"] = kSignalFastBack;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalEndFastBack:
      jsonObject["signal"] = kSignalEndFastBack;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;

  case kSignalList:
      //When you click on Dir instead of File
      break;
  case kSignalLang:
      jsonObject["signal"] = kSignalLang;
      jsonObject["lang"] = params["lang"].toString();
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  case kSignalMute:
      jsonObject["signal"] = kSignalMute;
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      if (m_socket != NULL) {
          m_socket->write(bytes.data(), bytes.length());
          m_socket->flush();
      }
      break;
  default:
      break;
  }
}


client::~client()
{
    m_socket->disconnectFromServer();
    m_running=false;
    m_clientLoopThread.waitForFinished();
}
