#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    server s;
    automate m;
    w.show();

    QObject::connect(&w, SIGNAL(signal_on()), &s, SLOT(ui_on()));
    QObject::connect(&m, SIGNAL(signalMachine(signalType, QVariantMap)), &s, SLOT(message(signalType, QVariantMap)));
    QObject::connect(&s, SIGNAL(signalFromServer(signalType,QVariantMap)), &m, SLOT(message(signalType, QVariantMap)));


    return a.exec();
}
