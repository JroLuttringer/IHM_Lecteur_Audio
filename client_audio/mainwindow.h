#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void sl_play();
    void sl_pause();
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
