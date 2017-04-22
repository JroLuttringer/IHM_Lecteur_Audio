#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QTimer>
#include <QDebug>


//Definir les types de signaux qu'il va recevoir du serveur
// ainsi que ceux qu'il va renvoyer vers le serveur(donc les clients)
enum signalType {
    kSignalPlay,
    kSignalPause
};

class automate : public QObject
{
    Q_OBJECT
public:
    explicit automate(QObject *parent = 0);

private:
    QTimer *songTimer;

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
    void setPause();
//    void setStop();
//    void setMute();


public slots:
    // Messages reçus du serveur (qu'il a reçu de l'UI = client)
    void message(signalType, QVariantMap);

};

#endif // AUTOMATE_H
