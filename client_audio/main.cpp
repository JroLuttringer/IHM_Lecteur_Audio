/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    client c;
    w.show();

    QObject::connect(&w, SIGNAL(signalToClient(signalType,QVariantMap)), &c, SLOT(messageFromUI(signalType, QVariantMap)));
    QObject::connect(&c, SIGNAL(signalFromClient(signalType,QVariantMap)), &w, SLOT(messageFromClient(signalType,QVariantMap)));
    return a.exec();
}
