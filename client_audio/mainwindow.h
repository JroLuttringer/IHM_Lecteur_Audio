/*
 * Copyright Cyrille MULLER Jean-Romain LUTTRINGER
 * UFR de Mathématiques et d'Informatique
 * Université de Strasbourg
 * © 2017
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QSlider>
#include <QMouseEvent>
#include "client.h"

class MySlider : public QSlider
{
public:
    MySlider(QWidget *parent):QSlider(parent) {}
protected:
  void mousePressEvent ( QMouseEvent * event )
  {
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()+1) * event->x()) / width() ) ;

        event->accept();
    }
    QSlider::mousePressEvent(event);
  }
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *song_timer;
    QTime *time_value;
    QTime *time_duration;
    //To be able to pause and resume timer
    int pause_ms;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool slider_is_pressed;
    Ui::MainWindow *ui;

signals:
    void signalToClient(signalType, QVariantMap);

public slots:
    void closeEvent();
    void sl_play();
    void sl_pause();
    void sl_volume(int);

        void setDisplay_timer();
        void slider_song_pressed();
        void slider_song_released();

    void sl_stop();
    void sl_next();
    void sl_back();
    void sl_mute();
    void sl_lang_fra();
    void sl_lang_eng();
    void sl_lang_ger();
//    void sl_set_sound();
//    void sl_set_time();

    void messageFromClient(signalType, QVariantMap);
};

#endif // MAINWINDOW_H
