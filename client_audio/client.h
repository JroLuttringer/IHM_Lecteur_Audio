/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */


#ifndef CLIENT_H
#define CLIENT_H

#define SERVER_NAME "test"
#include <QObject>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>
enum signalType
{
    kSignalPlay,
    kSignalPause,
    kSignalVolume,
    kSignalInfo,
    kSignalStartup,
    kSignalTime
};

class client : public QObject
{
    Q_OBJECT
private:
    QLocalSocket *m_socket;
public:
    explicit client(QObject *parent = 0);
    void serverMessageLoop();
    bool m_running;
    QFuture<void> m_clientLoopThread;
    ~client();

signals:
    void signalFromClient(signalType, QVariantMap);

public slots:
    void sl_play();
    void sl_pause();
    void sl_volume(int);
    //initial message to ask for all info
    void sl_info();
    void messageFromUI(signalType, QVariantMap);
};

#endif // CLIENT_H
