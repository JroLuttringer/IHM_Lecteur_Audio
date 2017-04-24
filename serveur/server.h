#ifndef SERVER_H
#define SERVER_H

#define SERVER_NAME "test"

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>

#include "automate.h"
class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    ~server();
    void clientMessageLoop();
    void MPV_messageLoop();
private:
    QString song_name;
    QLocalServer *m_server;
    QLocalSocket *m_client=NULL;
    QLocalSocket *m_mpv=NULL;
    bool m_running;
    QFuture<void> m_serverLoopThread;
    bool m_running_mpv;
    QFuture<void> m_MPV_messageLoopThread;

signals:
    void signalFromServer(signalType, QVariantMap);
//    La boucle de réception tournera dans une tâche concurrente :

public slots:
    void message(signalType, QVariantMap);
    void ui_on();
    void connectionFromClient();
    void clientDisconnected();

    void pause_mpv();
    void play_mpv();
    void setVolume_mpv(int);
};

#endif // SERVER_H
