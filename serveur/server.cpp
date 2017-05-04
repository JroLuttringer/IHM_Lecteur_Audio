#include "server.h"


server::server(QObject *parent) :
    QObject(parent),
    m_server(new QLocalServer(this))
{
    // Je crée la socket
    startup = true;
    m_mpv = new QLocalSocket(this);
    m_mpv->connectToServer("/tmp/mpvsocket");

    // J'attend d'être co
    while (!(m_mpv->waitForConnected())){
        QThread::msleep(100);
        qDebug("waiiiting");
        m_mpv->connectToServer("/tmp/mpvsocket");

    }

    // on fait tourner la boucle de reception dans un thread
    this->m_MPV_messageLoopThread=QtConcurrent::run(this, &server::MPV_messageLoop);
    m_running_mpv =true;

    qRegisterMetaType<signalType>("signalType");
//    et on démarre la boucle



}

void server::connectionFromClient()
{   qDebug() << "Connection from client" << socket_list.size();
    if(socket_list.size() == 0)
    {
        m_running=true;
        m_test1 = m_server->nextPendingConnection();
        socket_list.append(m_test1);
        m_serverLoopThread=QtConcurrent::run(this, &server::clientMessageLoop);
            connect(m_test1, SIGNAL(disconnected()), m_test1, SLOT(deleteLater()));
            connect(m_test1, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        return;
    }
    else if(socket_list.size() > 0)
    {
        m_test2 = m_server->nextPendingConnection();
        socket_list.append(m_test2);
        connect(m_test2, SIGNAL(disconnected()), m_test2, SLOT(deleteLater()));
        connect(m_test2, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        return;
    }
    else qDebug() << "Error with new clients";
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
//    if(pos==1) m_running2 =false;
}


void server::clientMessageLoop()
{
    int c = 0;
    if (socket_list.size()) m_client = socket_list.at(c);
    while (m_running)
    {
        QDataStream in(m_client);
        if (in.atEnd()){ // Rien dans la file d'attente
            c = (c+1) % (socket_list.size());
            m_client = socket_list.at(c);
            QThread::msleep(50); // On attend 1/10s et on continue
        continue;
        }
        QString str = QString(in.device()->readLine());
    //    Et on traite ce flux qui est du JSON
        QByteArray a = str.toUtf8();
        QJsonParseError error;
        QJsonDocument jDoc = QJsonDocument::fromJson(a,&error);
        QJsonObject jsonObject=jDoc.object();
        qDebug() << str;
        QVariantMap params;
        if (!jsonObject.contains("signal"))
        {
            qDebug() << "no signal, this is a disconnect";
            continue;
        }
        switch(jsonObject["signal"].toInt())
        {
            case kSignalPlay:
            emit signalFromServer(kSignalPlay, params);
                break;
            case kSignalPause:
            emit signalFromServer(kSignalPause, params);
                break;
            case kSignalInfo:
            emit signalFromServer(kSignalInfo, params);
                break;
            case kSignalVolume:
            params.insert("volume", jsonObject["volume"].toInt());
            emit signalFromServer(kSignalVolume, params);
                break;
            case kSignalStartup:
            emit signalFromServer(kSignalStartup, params);
            break;
            case kSignalTime:
            params.insert("time_change", jsonObject["time_change"].toInt());
            emit signalFromServer(kSignalTime, params);
                break;
            case kSignalTree:
                break;
            case kSignalStop:
            emit signalFromServer(kSignalStop, params);
                break;
            case kSignalNext:
            emit signalFromServer(kSignalNext, params);
                break;
            case kSignalFast:
            emit signalFromServer(kSignalFast, params);
                break;
            case kSignalEndFast:
            emit signalFromServer(kSignalEndFast, params);
                break;
            case kSignalBack:
            emit signalFromServer(kSignalBack, params);
                break;
            case kSignalFastBack:
                break;
            case kSignalEndFastBack:
                break;
            case kSignalSong:
//                params.insert("song_change", jsonObject["song_name"].toString());
                emit signalFromServer(kSignalSong, jsonObject.toVariantMap());
                break;
            case kSignalList:
                break;
            case kSignalLang:
            emit signalFromServer(kSignalLang, jsonObject.toVariantMap());
                break;
            case kSignalMute:
            emit signalFromServer(kSignalMute, jsonObject.toVariantMap());
                break;
        case kSignalQuit:
            qDebug() << "client sent quit message";
            break;
            default:
                qDebug() << "not yet implemented";
            break;
        }
    }
}

void server::ui_on()
{
    QVariantMap p;
    emit signalFromServer(kSignalSetup, p);
    qDebug("Turning ON Server... Waiting for Clients...");


    QString serverName(SERVER_NAME);
    QLocalServer::removeServer(serverName);
    if (!m_server->listen(serverName)) {
//    gestion d’erreur...;
    return;
    }
    connect(m_server, SIGNAL(newConnection()), this, SLOT(connectionFromClient()));
    qDebug() << "eof creator" << socket_list.size();

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
      jsonObject.insert("signal",kSignalPlay);
      jsonObject.insert("pause_ms", params["pause_ms"].toInt());
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      qDebug("le serveur a reçu play de l'automate, je dois envoyer play aux clients");
      send_bytes_to_clients(bytes);
      break;
  case kSignalPause:
      pause_mpv();
      jsonObject.insert("signal",kSignalPause);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      qDebug("le serveur a reçu pause de l'automate, je dois envoyer pause aux clients");
      send_bytes_to_clients(bytes);
      break;
  case kSignalVolume:
      volume = params["volume"].toLongLong();
      setVolume_mpv(volume);
      jsonObject.insert("signal", kSignalVolume);
      jsonObject.insert("volume", volume);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      //tell clients the volume has changed
      break;

  case kSignalInfo:
          jsonObject = jsonObject.fromVariantMap(params);
          bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
          send_bytes_to_clients(bytes);
      break;
  case kSignalEvent:
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalStartup:
      send_tree_from_file();

      break;
  case kSignalTime:
        t = params["time_change"].toInt();
        params["signal"] = kSignalTime;
        set_time_mpv(t);
        qDebug() << "setting time to " << t;
        jsonObject = jsonObject.fromVariantMap(params);
        bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
        send_bytes_to_clients(bytes);
      break;
  case kSignalTree:
      send_tree_from_file();
      break;
  case kSignalStop:
      pause_mpv();
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalNext:
      next_mpv();
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalFast:
      set_speed(2);
      params["signal"]=kSignalFast;
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalEndFast:
      set_speed(1);
      params["signal"]=kSignalEndFast;
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalBack:
      back_mpv();
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalFastBack:
//      set_speed(2);
      break;
  case kSignalEndFastBack:
//      set_speed(2);
      break;
  case kSignalSong:
        load_file_mpv(params["song_name"].toString());
        //send info to client
//        QThread::msleep(1000);
////        p["song_name"] = song_name;
////        p["duration"] = song_duration;
////        qDebug() << "in kSigSong sending dur=" << song_duration << " and name = " << song_name;
////        emit signalFromServer(kSignalInfo, p);
      break;
  case kSignalList:
      break;
  case kSignalLang:
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalMute:
      mute_mpv(params["muted"].toBool());
      jsonObject = jsonObject.fromVariantMap(params);
      bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
      send_bytes_to_clients(bytes);
      break;
  case kSignalSave:
//       save_preferences();
      break;
  case kSignalSetup:
      qDebug() << "asking ui for path";
        emit signalToUI(kSignalPath, params);
      break;
  case kSignalPath:
      load_file_mpv( params["file_path"].toString() );
      QThread::msleep(200);
      mute_mpv( params["muted"].toBool() ); //= muted;
      if (! params["playing"].toBool() )
          emit signalFromServer(kSignalPause, p);
      set_time_mpv( params["time-pos"].toInt() );
      break;

  default:
      break;
  }
}

void server::send_bytes_to_clients(QByteArray bytes)
{
    for(int i=0; i<socket_list.count(); i++)
    {
        if (m_test1) m_test1 = socket_list.at(i);
        if (m_test1 != NULL)
        {
//            qDebug() << "not null";
            m_test1->write(bytes.data(), bytes.length());
            m_test1->flush();
        }
    }
}


void server::send_tree_from_file()
{
    QFile file("./save.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;
    while (!in.atEnd())
       {
          line = line + in.readLine() + "\n";

       }

    QJsonObject jsonObject;
    QByteArray bytes;
    jsonObject.insert("signal",kSignalTree);
    jsonObject.insert("data", line);
    bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";

    send_bytes_to_clients(bytes);
    file.close();
}


void server::load_file_mpv(QString file_name)
{

//    'ytdl-format' << 'bestvideo+bestaudio/best';

    qDebug() << "loadfile mpv : " << file_name;
    QJsonObject jsonObject;
    QJsonArray request;
//    qDebug() << file_name;
    request << "loadfile" << file_name;
    jsonObject.insert("command",request);
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
    QVariantMap params;
    emit signalFromServer(kSignalPlay, params);

}

void server::set_time_mpv(int t){
    qDebug() << "setting time to =" << t;
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
    qDebug() << "pausing mpv";
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
    qDebug() << "sending play to PMV";
    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::stop_mpv(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
    request << "stop";
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::mute_mpv(bool mute_value){
    qDebug() << "setting mpv mute" << mute_value;
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",false]
    request << "set_property" << "mute" << mute_value;
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::next_mpv(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "playlist-next";
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::back_mpv(){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "playlist-prev";
    jsonObject.insert("command",request);

    // Je l'envoie sur la socket
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (m_mpv != NULL) {
        m_mpv->write(bytes.data(), bytes.length());
        m_mpv->flush();
    }
}

void server::set_speed(float speed){
    // Je crée des objets JSON pour préparer la requete
    QJsonObject jsonObject;
    QJsonArray request;

    // Je crée une requete de la forme " command :["set_property","pause",true]
    request << "set_property" << "speed" << speed;
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
    bool next = false;
    while(m_running_mpv){
        QDataStream in (m_mpv);
        if (in.atEnd()) { //rien dans la file
            QThread::msleep(100); // on wait un temps arbitraire parce que c'est la meilleure
            // technique du monde et que ça marche dans tous les domaines
             continue;
        }
        QString str = QString(in.device()->readLine());
        if(str == "") continue;
        qDebug() << "From MPV : " << str;
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
                send_startup();
                qDebug() << "Song_name demandée : " << song_name;
                    break;
                case 2:
                song_duration = jsonObject["data"].toDouble();
                qDebug() << "Song_duration demandée : " << song_duration;
                send_startup();
                    break;
                case 3:
                volume = jsonObject["data"].toDouble();
                qDebug() << "Song_volume demandée : " << volume;
                    break;

                case 4:
                song_time = std::max(0.0,jsonObject["data"].toDouble());
                qDebug() << "Song_time demandée : " << song_time;
                if (next && !startup)
                {
                    QVariantMap p;
                    p["song_name"] = song_name;
                    p["duration"] = song_duration;
                    p["time_change"] = song_time;
                    emit signalFromServer(kSignalTime, p);
                    emit signalFromServer(kSignalInfo, p);
                    next = false;
                    startup = false;
                    qDebug() << "sent time and info = " << song_time;
                }
                startup = false;
                    break;
                default:
                    break;
            }
        }
        if (jsonObject["event"] == "start-file")
        {
//                send_startup();
//                qDebug() <<" sending startup ";
        }
        if (jsonObject["event"] == "tracks-changed")
        {
            get_file_name();
            get_duration();
            get_volume();
            QThread::msleep(100);
            get_time();
            next = true;
        }
    }
}

void server::send_startup()
{
    QVariantMap p;
//    while (startup) QThread::usleep(100);
//    qDebug() << "Sending start signal song_dur = " << song_duration;
    p["song_name"] = song_name;
    p["duration"] = song_duration;
    emit signalFromServer(kSignalEvent, p);
}

server::~server()
{
//    save_preference();
    m_running=false;
    m_serverLoopThread.waitForFinished();
}
