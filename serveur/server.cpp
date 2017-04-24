#include "server.h"


server::server(QObject *parent) :
    QObject(parent),
    m_server(new QLocalServer(this))
{
    // Je crée la socket
    m_mpv = new QLocalSocket(this);


    // Je connect la socket au server MPV
    // ( j'ai lancé MPV avec cet argument )
    m_mpv->connectToServer("/tmp/mpvsocket");

    // J'attend d'être co
    while (!(m_mpv->waitForConnected())){
        QThread::msleep(100);
        qDebug("waiiiting");
        m_mpv->connectToServer("/tmp/mpvsocket");
    }
    {
        // si je suis pas co, j'affiche une erreur
        qDebug("letsgo mpv");
    }

    // on fait tourner la boucle de reception dans un thread
    this->m_MPV_messageLoopThread=QtConcurrent::run(this, &server::MPV_messageLoop);
    m_running_mpv =true;




    qRegisterMetaType<signalType>("signalType");
//    et on démarre la boucle
    m_running=true;
    m_serverLoopThread=QtConcurrent::run(this, &server::clientMessageLoop);


    QString serverName(SERVER_NAME);
    QLocalServer::removeServer(serverName);
    if (!m_server->listen(serverName)) {
//    gestion d’erreur...;
    return;
    }
    connect(m_server, SIGNAL(newConnection()), this, SLOT(connectionFromClient()));
}

void server::connectionFromClient()
{
    if(m_client) return; // Un seul client
    m_client= m_server->nextPendingConnection();
    connect(m_client, SIGNAL(disconnected()), m_client, SLOT(deleteLater()));
    connect(m_client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

//Quand un client se déconnecte, on l’annule :
void server::clientDisconnected()
{
    m_client = nullptr;
}


void server::clientMessageLoop()
{
    while (m_running){
    QDataStream in(m_client);
    if (in.atEnd()){ // Rien dans la file d'attente
    QThread::msleep(100); // On attend 1/10s et on continue
    continue;
    }
    QString str = QString(in.device()->readLine());
//    Et on traite ce flux qui est du JSON
    QByteArray a = str.toUtf8();
    QJsonParseError error;
    QJsonDocument jDoc = QJsonDocument::fromJson(a,&error);
    QJsonObject jsonObject=jDoc.object();
    qDebug() << str;
    if (jsonObject["signal"] == "play_client")
    {
        qDebug("i received play from client, sending to automate");
        QVariantMap params;
        emit signalFromServer(kSignalPlay, params);
    }
    if (jsonObject["signal"] == "pause_client")
    {
        qDebug("i received pause from client, sending to automate");
        QVariantMap params;
        emit signalFromServer(kSignalPause, params);
    }
    if (jsonObject["signal"] == "get_info")
    {
        qDebug("i received get_info from client, sending to automate");
        QVariantMap params;
        emit signalFromServer(kSignalInfo, params);
    }
    if (jsonObject.contains("volume"))
    {
        QVariantMap params;
        int volume = jsonObject["volume"].toVariant().toLongLong();
        params.insert("volume", volume);
        emit signalFromServer(kSignalVolume, params);
//
    }

//    QByteArray a=str.toUtf8();
//    QJsonParseError error;
//    QJsonDocument jDoc=QJsonDocument::fromJson(a, &error);
//    QJsonObject jsonObject=jDoc.object();
    }
}

void server::ui_on()
{
    qDebug("ui says to turn on");
}

void server::message(signalType sig, QVariantMap params) {
  switch(sig){
  case kSignalPlay:
      play_mpv();
      qDebug("le serveur a reçu play de l'automate, je dois envoyer play aux clients");
      if (m_client != NULL)
      {

          // Je crée des objets JSON pour préparer la requete
          QJsonObject jsonObject;
          jsonObject.insert("signal","play");

          // Je l'envoie sur la socket
          QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

//          QByteArray bytes = "play_serveur";

          m_client->write(bytes.data(), bytes.length());
          m_client->flush();
      }
      break;
  case kSignalPause:
      pause_mpv();
//      qDebug("le serveur a reçu pause de l'automate, je dois envoyer pause aux clients");
      if (m_client != NULL)
      {
          QJsonObject jsonObject;
          jsonObject.insert("signal","pause");

          // Je l'envoie sur la socket
          QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

          m_client->write(bytes.data(), bytes.length());
          m_client->flush();
      }
      break;
  case kSignalVolume:

      int vol;
      vol= params["volume"].toLongLong();

      setVolume_mpv(vol);
      //tell clients the volume has changed
  default:

  case kSignalInfo:
      if (m_client != NULL)
      {
          QJsonObject jsonObject;
          jsonObject.insert("signal","info");
          jsonObject.insert("song_name","test");
          jsonObject.insert("duration",360);
          jsonObject.insert("time",15);
          jsonObject.insert("volume",75);
          jsonObject.insert("mute",false);
          jsonObject.insert("play",false);

          // Je l'envoie sur la socket
          QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

          m_client->write(bytes.data(), bytes.length());
          m_client->flush();
      }
      break;
  }
}














//fonction vers mpv

void server::pause_mpv(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "set_property" << "pause" << true;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::play_mpv(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
    request << "set_property" << "pause" << false;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::setVolume_mpv(int vol){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
    request << "set_property" << "volume" << vol;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

//void MainWindow::get_file_name(){
//    // Je crée des objets JSON pour préparer la requete
//    QJsonObject jsonObject;
//    QJsonArray request;

//    // Je crée une requete de la forme " command :["get_property","filename"]
//    request << "get_property" << "filename";
//    jsonObject.insert("command",request);

//    // Je l'envoie sur la socket
//    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
//    if (m_socket != NULL) {
//        m_socket->write(bytes.data(), bytes.length());
//        m_socket->flush();
//    }
//}

// Boucle de reception
void server::MPV_messageLoop(){
    while(m_running_mpv){
        QDataStream in (m_mpv);
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
//            qDebug() << "Demande faite avec succes";
            // si j'ai un champs "data" dans la réponse, c'est que j'ai demandé un renseignement
            if (jsonObject.contains("data")){
//            qDebug() << "Data demandée : " << jsonObject["data"];
            }
        }

    }
}

server::~server()
{
    m_running=false;
    m_serverLoopThread.waitForFinished();
}
