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
    sl_info();
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
        if (jsonObject["signal"]== "info") emit signalFromClient(kSignalInfo, jsonObject.toVariantMap());
        if (jsonObject["signal"]== "play") emit signalFromClient(kSignalPlay, jsonObject.toVariantMap());
        if (jsonObject["signal"]== "pause") emit signalFromClient(kSignalPause, jsonObject.toVariantMap());
        if (jsonObject["signal"]== "tree_init" && !setup)
        {
            emit signalFromClient(kSignalTree, jsonObject.toVariantMap());
            setup = true;
        }
        if (jsonObject.contains("time_change")) emit signalFromClient(kSignalTime, jsonObject.toVariantMap());

    }
}

void client::sl_info()
{
    QJsonObject jsonObject;
    jsonObject["signal"] ="get_info";

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
    jsonObject["signal"] ="play_client";

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
    jsonObject["signal"] = "pause_client";

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
      jsonObject["time_change"] = params["time_change"].toInt();
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
