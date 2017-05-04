#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    server s;
//        QThread::usleep(1000);
    automate m;
    w.show();



    QObject::connect(&w, SIGNAL(signal_on()), &s, SLOT(ui_on()));

    QObject::connect(&w, SIGNAL(change_song(QString)), &s, SLOT(load_file_mpv(QString)));
    QObject::connect(&w, SIGNAL(signalUI(signalType, QVariantMap)), &s, SLOT(message(signalType, QVariantMap)));
    QObject::connect(&w, SIGNAL(signalSave(signalType, QVariantMap)), &m, SLOT(message(signalType, QVariantMap)));
    QObject::connect(&m, SIGNAL(signalMachine(signalType, QVariantMap)), &s, SLOT(message(signalType, QVariantMap)));
    QObject::connect(&s, SIGNAL(signalFromServer(signalType,QVariantMap)), &m, SLOT(message(signalType, QVariantMap)));


    return a.exec();
}
