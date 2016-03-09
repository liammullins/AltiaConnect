#include "atcpservercontroller.h"

//extern ATCPServerController *tcpServer;
AConnectionManager *connectionManager;
MainWindow *main_window;

ATCPServerController::ATCPServerController(QObject *parent) :
    QObject(parent)
{

    /* init our advertisement variables */
    allCastAdv.p_stopped = false;
    allCastAdv.p_duration = -1;
    allCastAdv.p_position = -1;
    allCastAdv.p_paused = false;
    allCastAdv.p_captions = false;
}

void ATCPServerController::setupConnection(int port)
{

    firstTimeConnect = true;

    connect(&p_server, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));

    if (p_server.isListening()==false)
    {
        p_server.listen(QHostAddress::AnyIPv4, port);

        #ifdef NETWORK_DEBUG
            qDebug() << "listening on port:: " << port;
        #endif
    }
}

ATCPServerController::~ATCPServerController()
{
    p_server.close();
}

void ATCPServerController::acceptConnection()
{
    p_client = p_server.nextPendingConnection();
    /* connect our connection to the read operation */
    p_client->connect(p_client, SIGNAL(readyRead()),
                      this, SLOT(startRead()));
}
void ATCPServerController::setClientMessage(QString msg)
{
    sendClientMessage = msg;
}

void ATCPServerController::processStream(QString rawMessage)
{
    /* Position Message: this message is passed to the renderer to dictate scrub position */
    if (rawMessage.indexOf("\"position\"")>0)
    {
        QString final = rawMessage.mid(rawMessage.indexOf("\r\n\r\n{")+4,rawMessage.length());
        QJsonDocument jsonDoc = QJsonDocument::fromJson(final.toUtf8());
        QJsonObject jo = jsonDoc.object();
        int pos = jo["position"].toInt();
        allCastAdv.p_position = pos;
        main_window->setPlayerPosition(pos);

        return;
    }
    /* Some messages are RESTful */
    if (rawMessage.indexOf("/api/v1/pause")>0)
    {
        allCastAdv.p_paused = true;
        main_window->ui->pbPlayPause->toggle();
        return;
    }
    /* Some messages are RESTful */
    if (rawMessage.indexOf("/api/v1/resume")>0)
    {
        allCastAdv.p_paused = false;
        main_window->ui->pbPlayPause->toggle();
        return;
    }
    /* Some messages are RESTful */
    if (rawMessage.indexOf("/api/v1/stop")>0)
    {
        allCastAdv.p_stopped = true;
        main_window->player->stop();
    }
}

void ATCPServerController::startRead()
{

    QString raw = p_client->readAll();
    processStream(raw);
    sendAllCastAdvertisement(/*p_stopped,p_duration,p_position,p_paused, p_captions*/);

    #ifdef NETWORK_DEBUG
        qDebug() << raw<<"\n";
    #endif

    if (raw.indexOf("\"url\"")==-1)
    {
        /* In most broadcast messages, there isn't anything to do. We just want to process the messages that have directions */
        return;
    }
    try
    {
        QString final = raw.mid(raw.indexOf("\r\n\r\n{")+4,raw.length());
        QJsonDocument jsonDoc = QJsonDocument::fromJson(final.toUtf8());
        QJsonObject jo = jsonDoc.object();
        QString fileUrl = jo["url"].toString();
        QString a_a = jo["albumArt"].toString();

        #ifdef NETWORK_DEBUG
            qDebug() << "\nalbum art " << a_a<<"";
        #endif

        albumArtLink = a_a;
        if (!fileUrl.isEmpty())
        {
            emit servedFile(fileUrl);
            #ifdef NETWORK_DEBUG
                qDebug()<<"emitting file:  "<< fileUrl;
            #endif
        }
    }
    catch(...)
    {
        #ifdef NETWORK_DEBUG
            qDebug() << "READ ERROR";
        #endif
    }
}

void ATCPServerController::sendAllCastAdvertisement(/*bool stopped, qint64 duration, qint64 position, bool paused, bool captions*/)
{

    QString advertisement ="HTTP/1.1 200 OK\r\n\r\n"
                                              "{\"stopped\":"+bool_cast(allCastAdv.p_stopped)+","
                                               "\"duration\":"+QString::number(allCastAdv.p_duration)+","
                                               "\"position\":"+QString::number(allCastAdv.p_position)+","
                                               "\"paused\":"+bool_cast(allCastAdv.p_paused)+","
                                               "\"captions\":"+bool_cast(allCastAdv.p_captions)+"}";
    /* Write our advertisement to the socket */
    p_client->write(advertisement.toStdString().c_str());

#ifdef NETWORK_DEBUG
    qDebug() << advertisement;
#endif

}
