#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Je crée la socket
    m_socket = new QLocalSocket(this);


    // Je connect la socket au server MPV
    // ( j'ai lancé MPV avec cet argument )
    m_socket->connectToServer("/tmp/mpvsocket");

    // J'attend d'être co
    if (m_socket->waitForConnected()){
        qDebug("Je suis co");
    } else {
        // si je suis pas co, j'affiche une erreur
        qDebug("Error socket connection");
    }

    // on fait tourner la boucle de reception dans un thread
    this->m_MPV_messageLoopThread=QtConcurrent::run(this, &MainWindow::MPV_messageLoop);
    m_running =true;

    ui->setupUi(this);
    connect(ui->Pause, SIGNAL(pressed()), this, SLOT(pause()));
    connect(ui->Play, SIGNAL(pressed()), this, SLOT(play()));
    connect(ui->name, SIGNAL(pressed()), this, SLOT(get_file_name()));
}

void MainWindow::pause(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "set_property" << "pause" << true;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void MainWindow::play(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
    request << "set_property" << "pause" << false;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

void MainWindow::get_file_name(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["get_property","filename"]
    request << "get_property" << "filename";
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_socket != NULL) {
        m_socket->write(bytes.data(), bytes.length());
        m_socket->flush();
    }
}

// Boucle de reception
void MainWindow::MPV_messageLoop(){
    while(m_running){
        QDataStream in (m_socket);
        if (in.atEnd()) { //rien dans la file
            QThread::msleep(100); // on wait un temps arbitraire parce que c'est la meilleure
            // technique du monde et que ça marche dans tous les domaines
             continue;
        }
        QString str = QString(in.device()->readLine());
        if(str == "") continue;
        QByteArray a = str.toUtf8();
        QJsonParseError error;
        QJsonDocument jDoc = QJsonDocument::fromJson(a,&error);
        QJsonObject jsonObject=jDoc.object();
        // je lis le JSON comme un tableau
        if (jsonObject["error"] == "success")
        {
            qDebug() << "Demande faite avec succes";
            // si j'ai un champs "data" dans la réponse, c'est que j'ai demandé un renseignement
            if (jsonObject.contains("data")){
            qDebug() << "Data demandée : " << jsonObject["data"];
            }
        }

    }
}

MainWindow::~MainWindow()
{
   m_socket->disconnectFromServer();
   m_running = false;
   m_MPV_messageLoopThread.waitForFinished();
    delete ui;
}
