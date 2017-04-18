#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QLocalSocket"
#include "QtConcurrent/QtConcurrent"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    // Le destructeur devra être modifié
    // pour qu'il déco la socket
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Je crée une socket locale pour communiquer
    // avec MPV
    QLocalSocket* m_socket;

    // Je crée une fonction d'envoie asynchrone
    // (i.e qui tourne dans un thread)
    // à voir en fait si y'a pas que besoin de faire tourner
    // la boucle de reception dans un thread
    void send_server();

    // Boucle de reception
    void MPV_messageLoop();
    bool m_running;
    QFuture<void> m_MPV_messageLoopThread;

public slots :
    void pause();
    void play();
    void get_file_name();
};

#endif // MAINWINDOW_H
