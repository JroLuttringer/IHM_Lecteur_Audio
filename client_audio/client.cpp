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
        qDebug() << qPrintable(str);
        if(str=="") continue; // Evitons les lignes vides.
        QByteArray a=str.toUtf8();
        QJsonParseError error;
        QJsonDocument jDoc=QJsonDocument::fromJson(a, &error);
        QJsonObject jsonObject=jDoc.object();
    }
}

void client::sl_play()
{
    //send socket play
    if (m_socket != NULL) {
        m_socket->write("play_client");
        m_socket->flush();
    }
}
void client::sl_pause()
{
    //send socket pause
    if (m_socket != NULL) {
        m_socket->write("pause_client");
        m_socket->flush();
    }
}


client::~client()
{
    m_socket->disconnectFromServer();
    m_running=false;
    m_clientLoopThread.waitForFinished();
}
