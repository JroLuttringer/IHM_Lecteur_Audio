/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    client *c_test;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void closeEvent();
    void sl_stop();
    void sl_next();
    void sl_back();
    void sl_mute();
    void sl_lang_fra();
    void sl_lang_eng();
    void sl_lang_ger();
//    void sl_set_sound();
//    void sl_set_time();
};

#endif // MAINWINDOW_H
