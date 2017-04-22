#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "automate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
//    server *s_test;
signals:
    void signal_on();

public slots:
    void send_pressed();
};

#endif // MAINWINDOW_H
