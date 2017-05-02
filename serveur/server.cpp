#include "server.h"


server::server(QObject *parent) :
    QObject(parent),
    m_server(new QLocalServer(this))
{
    // Je crée la socket
    startup = true;
    m_mpv = new QLocalSocket(this);

//    m_test1 = new QLocalSocket(this);
//    socket_list = new QList(QLocalSocket);

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
        get_file_name();
        get_duration();
        get_volume();
        get_time();
        qDebug("letsgo mpv");
    }

    // on fait tourner la boucle de reception dans un thread
    this->m_MPV_messageLoopThread=QtConcurrent::run(this, &server::MPV_messageLoop);
    m_running_mpv =true;




    qRegisterMetaType<signalType>("signalType");
//    et on démarre la boucle


    QString serverName(SERVER_NAME);
    QLocalServer::removeServer(serverName);
    if (!m_server->listen(serverName)) {
//    gestion d’erreur...;
    return;
    }
    connect(m_server, SIGNAL(newConnection()), this, SLOT(connectionFromClient()));
    qDebug() << "eof creator" << socket_list.size();


}

void server::connectionFromClient()
{   qDebug() << "Connection from client" << socket_list.size();
    if(socket_list.count() == 0)
    {
        m_running=true;

        m_test1 = m_server->nextPendingConnection();
        socket_list.append(m_test1);
        m_serverLoopThread=QtConcurrent::run(this, &server::clientMessageLoop);
            connect(m_test1, SIGNAL(disconnected()), m_test1, SLOT(deleteLater()));
            connect(m_test1, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        return;
    }
    else if(socket_list.count() == 1)
    {
        m_running2=true;

        m_test2 = m_server->nextPendingConnection();
        socket_list.append(m_test2);
        m_serverLoopThread2=QtConcurrent::run(this, &server::clientMessageLoop2);
        connect(m_test2, SIGNAL(disconnected()), m_test2, SLOT(deleteLater()));
        connect(m_test2, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        return;
    }
    else if(socket_list.count() == 2)
    {
        socket_list.append(m_server->nextPendingConnection());
        return;
    }
    else if(socket_list.count() == 3)
    {
        socket_list.append(m_server->nextPendingConnection());
        return;
    }
    else qDebug() << "Too many clients";
    qDebug() << "ça crash pas icic bouffon";
}

//Quand un client se déconnecte, on l’annule :
void server::clientDisconnected()
{
    QLocalSocket* send = qobject_cast<QLocalSocket*>( QObject::sender() );
    int pos = socket_list.indexOf(send);
    qDebug() << "deleting client " << pos;
    socket_list.removeAt(pos);
    send = nullptr;
    if(!pos) m_running = false;
    if(pos==1) m_running2 =false;
}


void server::clientMessageLoop()
{
    m_client = socket_list.at(0);
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
    if (jsonObject.contains("time_change"))
    {
        QVariantMap params;
        int time_change = jsonObject["time_change"].toInt();
        params.insert("time_change", time_change);
        emit signalFromServer(kSignalTime, params);
        qDebug() << "sending time change to machine with int : " << time_change;
    }
//    QByteArray a=str.toUtf8();
//    QJsonParseError error;
//    QJsonDocument jDoc=QJsonDocument::fromJson(a, &error);
//    QJsonObject jsonObject=jDoc.object();
    }
}


void server::clientMessageLoop2()
{
    m_client2 = socket_list.at(1);
    while (m_running2){
    QDataStream in(m_client2);
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
    if (jsonObject.contains("time_change"))
    {
        QVariantMap params;
        int time_change = jsonObject["time_change"].toInt();
        params.insert("time_change", time_change);
        emit signalFromServer(kSignalTime, params);
        qDebug() << "sending time change to machine with int : " << time_change;
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
    qDebug() << "Server got message from machine with code " << (sig);
    QVariantMap p;
    QJsonObject jsonObject;
    QByteArray bytes;
    int t;
  switch(sig){
  case kSignalPlay:
      play_mpv();
      jsonObject.insert("signal","play");
      jsonObject.insert("pause_ms", params["pause_ms"].toInt());
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

      qDebug("le serveur a reçu play de l'automate, je dois envoyer play aux clients");
      for(int i=0; i<socket_list.count(); i++)
      {
          if (socket_list.at(i) != NULL)
          {
              socket_list.at(i)->write(bytes.data(), bytes.length());
              socket_list.at(i)->flush();
          }
      }
      qDebug() << "where the fuck is it crashing play";
      break;
  case kSignalPause:
      pause_mpv();
      jsonObject.insert("signal","pause");
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

      qDebug("le serveur a reçu pause de l'automate, je dois envoyer pause aux clients");
      for(int i=0; i<socket_list.count(); i++)
      {
          if (m_test1) m_test1 = socket_list.at(i);
          if (m_test1 != NULL)
          {
              qDebug() << "not null";
              m_test1->write(bytes.data(), bytes.length());
              m_test1->flush();
          }
      }
      qDebug() << "fin pause";
      break;
  case kSignalVolume:

      volume = params["volume"].toLongLong();

      setVolume_mpv(volume);
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      for(int i=0; i<socket_list.count(); i++)
      {
          if (m_test1) m_test1 = socket_list.at(i);
          if (m_test1 != NULL)
          {
              qDebug() << "not null";
              m_test1->write(bytes.data(), bytes.length());
              m_test1->flush();
          }
      }
      //tell clients the volume has changed
      break;

  case kSignalInfo:

          jsonObject = jsonObject.fromVariantMap(params);
          bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
          for(int i=0; i<socket_list.count(); i++)
          {
              if (m_test1) m_test1 = socket_list.at(i);
              if (m_test1 != NULL)
              {
                  qDebug() << "not null";
                  m_test1->write(bytes.data(), bytes.length());
                  m_test1->flush();
              }
          }
          qDebug() << "sent info to all clients now sending trees";
          send_tree_from_file();
      break;
  case kSignalStartup:

      break;
  case kSignalTime:
        t = params["time_change"].toInt();
        set_time_mpv(t);
        jsonObject = jsonObject.fromVariantMap(params);
        bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
        for(int i=0; i<socket_list.count(); i++)
        {
            if (m_test1) m_test1 = socket_list.at(i);
            if (m_test1 != NULL)
            {
                qDebug() << "not null";
                m_test1->write(bytes.data(), bytes.length());
                m_test1->flush();
            }
        }
      break;

  default:
      break;
  }
}

void server::send_tree_from_file()
{
    QFile file("/home/cyrille/test/save.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;
    while (!in.atEnd())
       {
          line = line + in.readLine() + "\n";

       }

    QJsonObject jsonObject;
    QByteArray bytes;
    jsonObject.insert("signal","tree_init");
    jsonObject.insert("data", line);
    bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    for(int i=0; i<socket_list.count(); i++)
    {
        if (m_test1) m_test1 = socket_list.at(i);
        if (m_test1 != NULL)
        {
            qDebug() << "not null";
            m_test1->write(bytes.data(), bytes.length());
            m_test1->flush();
        }
    }
    file.close();
}












//fonction vers mpv


void server::load_file_mpv(QString file_name)
{
    QJsonObject jsonObject;
    QJsonArray request;
    request << "loadfile" << file_name;
    jsonObject.insert("command",request);
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::set_time_mpv(int t){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "set_property" << "time-pos" << t;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}


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

void server::get_file_name(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["get_property","filename"]
    request << "get_property" << "filename";
    jsonObject.insert("command",request);
    jsonObject.insert("request_id", 1);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::get_duration(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["get_property","filename"]
    request << "get_property" << "duration";
    jsonObject.insert("command",request);
    jsonObject.insert("request_id", 2);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::get_volume(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["get_property","filename"]
    request << "get_property" << "volume";
    jsonObject.insert("command",request);
    jsonObject.insert("request_id", 3);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::get_time(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["get_property","filename"]
    request << "get_property" << "time-pos";
    jsonObject.insert("command",request);
    jsonObject.insert("request_id", 4);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

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
//        qDebug() << str;
        QByteArray a = str.toUtf8();
        QJsonParseError error;
        QJsonDocument jDoc = QJsonDocument::fromJson(a,&error);
        QJsonObject jsonObject=jDoc.object();
        // je lis le JSON comme un tableau
        if (jsonObject["error"] == "success")
        {
            switch(jsonObject["request_id"].toInt())
            {
                case 1:
                song_name = jsonObject["data"].toString();
                qDebug() << "Song_name demandée : " << song_name;
                    break;
                case 2:
                song_duration = jsonObject["data"].toDouble();
                qDebug() << "Song_duration demandée : " << song_duration;
                    break;
                case 3:
                volume = jsonObject["data"].toDouble();
                qDebug() << "Song_volume demandée : " << volume;
                    break;

                case 4:
                song_time = jsonObject["data"].toDouble();
                qDebug() << "Song_time demandée : " << song_time;
                if (startup)
                {
                    startup = false;
                    send_startup();
                }
                    break;
                default:
                    break;
            }
        }


    }
}

void server::send_startup()
{
    QVariantMap p;
    while (startup) QThread::usleep(100);
    qDebug() << "Sending start signal song_dur = " << song_duration;
    p["song_name"] = song_name;
    p["duration"] = song_duration;
    emit signalFromServer(kSignalStartup, p);
}

server::~server()
{
    m_running=false;
    m_serverLoopThread.waitForFinished();
}
