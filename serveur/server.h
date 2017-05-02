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
    void clientMessageLoop2();
    void MPV_messageLoop();


    QList<QLocalSocket*> socket_list;
    QLocalSocket *m_test1 = NULL;
    QLocalSocket *m_test2 = NULL;
    QLocalSocket *m_test3 = NULL;
    QLocalSocket *m_test4 = NULL;
private:
    int song_duration;
    QString song_name;
    bool muted;
    bool playing;
    bool startup;
    int volume;
    int song_time;


    QLocalServer *m_server;
    QLocalSocket *m_client;
    QLocalSocket *m_client2;
    QLocalSocket *m_mpv=NULL;
    bool m_running;
    bool m_running2;
    bool m_running3;
    bool m_running4;

    QFuture<void> m_serverLoopThread;
    QFuture<void> m_serverLoopThread2;
    bool m_running_mpv;
    QFuture<void> m_MPV_messageLoopThread;

signals:
    void signalFromServer(signalType, QVariantMap);
//    La boucle de réception tournera dans une tâche concurrente :

public slots:
    void message(signalType, QVariantMap);
    void ui_on();
    void send_startup();
    void connectionFromClient();
    void clientDisconnected();

    void set_time_mpv(int);
    void pause_mpv();
    void play_mpv();
    void get_file_name();
    void get_duration();
    void get_volume();
    void get_time();
    void setVolume_mpv(int);
    void load_file_mpv(QString);

    void send_tree_from_file();
};

#endif // SERVER_H
