#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QTimer>
#include <QTime>
#include <QDebug>


//Definir les types de signaux qu'il va recevoir du serveur
// ainsi que ceux qu'il va renvoyer vers le serveur(donc les clients)
enum signalType {
    kSignalPlay,
    kSignalPause,
    kSignalVolume,
    kSignalInfo,
    kSignalStartup,
    kSignalTime,
    kSignalTree,
    kSignalStop,
    kSignalNext,
    kSignalFast,
    kSignalEndFast,
    kSignalBack,
    kSignalFastBack,
    kSignalEndFastBack,
    kSignalSong,
    kSignalList,
    kSignalLang,
    kSignalMute,
    kSignalEvent
};

class automate : public QObject
{
    Q_OBJECT
public:
    explicit automate(QObject *parent = 0);
    bool startup;
    bool muted;
    bool playing;
    int volume = 100;
    int song_duration = 0;
    QString song_name;
    int pause_ms;

private:
    QTimer *songTimer;
    QTime *song_time;
    QStateMachine *machine;
    QState *play;
    QState *pause;

//    QState *stop;

    //Sous état? car independant des autres
//    QState *mute;
    //Rajouter pour le son

    // Les messages envoyés à l'UI /contraste avec les private slots
    void setupMessages();
    void start(bool); // On/Off
    void setPause(bool);
//    void changeVolume(int);

signals:
    // Le format de communication vers l'UI
    void signalMachine(signalType, QVariantMap);

    // Internal
    void signalPause();
    void signalPlay();

private slots:
    //messages internes, fonctions à appeler lors de reception de messages du serveur par ex.
    //complementaire des fonctions private
    void setPlay();
    void send_info();
    void send_event();
    void setPause();
    void setVolume(int);
    void startup_info();
    void increase_time();
//    void setStop();
//    void setMute();


public slots:
    // Messages reçus du serveur (qu'il a reçu de l'UI = client)
    void message(signalType, QVariantMap);

};

#endif // AUTOMATE_H
