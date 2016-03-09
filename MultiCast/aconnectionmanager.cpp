#include "aconnectionmanager.h"

MainWindow *m_window;
StaticFileController *staticFileController;
extern ATCPServerController *tcpServer;


AConnectionManager::AConnectionManager(QObject *parent, Ui::MainWindow *_ui) :
    QObject(parent),
    ui(_ui)
{
    /* get instance of mainwindow */
    m_window = static_cast<MainWindow *>(parent);
    ui->netTraffic->setVisible(false);
}

AConnectionManager::~AConnectionManager()
{
    stopHTTPServer();
}

void AConnectionManager::clearTable()
{
    ui->twIPHosts->clear();
}

void AConnectionManager::removeRow(int row)
{
    ui->twIPHosts->removeRow(row);
}

void AConnectionManager::updateRow(int row, QString ip, QString serverName)
{
    ui->twIPHosts->item(row,0)->setText(serverName);
    ui->twIPHosts->item(row,1)->setText(ip);
}

void AConnectionManager::addIPToTable(QString ip,QString serverName)
{
    ui->twIPHosts->insertRow(0);
    ui->twIPHosts->item(0,0)->setText(serverName);
    ui->twIPHosts->item(0,1)->setText(ip);
}

void AConnectionManager::stopHTTPServer()
{
    udpSocket->leaveMulticastGroup(groupAddress);
    udpSocket->disconnect();
    delete http_listener;
    delete tcpServer;
}

void AConnectionManager::startHTTPServer()
{
    QString binDir  = QCoreApplication::applicationDirPath();
    QFile file;
    QString configFileName;
    file.setFileName(binDir+"/config.ini");
    /* load the http config file - this must be included or fatal */
    if (file.exists())
    {
        configFileName = QDir(file.fileName()).canonicalPath();

        #ifdef NETWORK_DEBUG
            qDebug("using config file %s", qPrintable(configFileName));
        #endif
    }
    else
    {
        qFatal("config file not found");
    }

    // Load the configuration file
    QSettings* listenerSettings = new QSettings(configFileName, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,this);
    fileSettings->beginGroup("docroot");
    staticFileController = new StaticFileController(fileSettings,this);
    // Start the HTTP server
    http_listener = new HttpListener(listenerSettings, new AltiaUPnPController(this), this);
    /* update status in textbox */
    ui->teStatus->append("----------\nWeb Server Started...\n----------");

}
void AConnectionManager::setTrafficStatus(bool traffic)
{
    if(traffic)
    {
        ui->netTraffic->setVisible(true);
    }
    else
    {
        ui->netTraffic->setVisible(false);
    }
}
void AConnectionManager::processPendingDatagrams()
{

    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),&senderIP,&senderPort);
        ui->teStatus->append(tr("%1").arg(datagram.data()));
        /* this really should be based on the actual default gateway  */

                QString msg = "{\"port\":53515,\"name\":\"Altia Connect\",\"id\":\"Altia_Connect\","
                                          "\"width\":"+QString::number(m_window->videoWidget->width())+","
                                          "\"height\":"+QString::number(m_window->videoWidget->width())+","
                                           "\"mirror\":\"h264\","
                                           "\"audio\":\"pcm\","
                                           "\"subtitles\":\"text/vtt\","
                                           "\"proxyHeaders\":false,"
                                           "\"hls\":true,"
                                           "\"upsell\":false }";
                //audio : pcm;
                if (senderPort==1900)
                {
                    msg = "{\"port\":1900,\"name\":\"Altia Connect\",\"id\":\"Altia_Connect\",\"width\":1280,"
                                "\"height\":960,\"mirror\":\"h264\",\"audio\":\"pcm\",\"subtitles\":\"text/vtt\","
                                "\"proxyHeaders\":true,\"hls\":true,\"upsell\":false}";
                }

                datagram = msg.toStdString().c_str();
                udpSocket->writeDatagram(datagram.data(), datagram.size(),
                                         senderIP, senderPort);
                ui->teStatus->verticalScrollBar()->setValue(ui->teStatus->verticalScrollBar()->maximum());
            }

}
void AConnectionManager::startUPNPServer()
{
    groupAddress = QHostAddress("239.255.255.250");
    udpSocket = new QUdpSocket(this);
    //allcast 53515
    udpSocket->bind(QHostAddress::AnyIPv4, MCPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this,SLOT(processPendingDatagrams()));

    /* init tcp listener service */
    tcpServer = new ATCPServerController();
    /* Setup listener now that we have communication */
    tcpServer->setupConnection(MCPort);
    connect(tcpServer, SIGNAL(servedFile(QString)),
            m_window, SLOT(playMedia(QString)));

}

void AConnectionManager::setPort(int port)
{
    MCPort = port;
}

void AConnectionManager::setGroupIP(QString address)
{
    groupAddress = address;
}

void AConnectionManager::sendDiscoverMessage()
{
    /* Control Point Search */
    QString msg = "M-SEARCH * HTTP/1.1\r\n"
                               "HOST: "+groupAddress.toString()+":"+QString::number(MCPort)+"\r\n"
                               "MAN: \"ssdp:discover\"\r\n"
                               "MX: 5\r\n"
                               "ST: ssdp:all\r\n\r\n";

    ui->teStatus->append(tr("****Sending M-SEARCH...****\n%1").arg(msg));
    //ui->lwStatus->addItem(tr("Sending M-SEARCH...\n%1").arg(msg));
    QByteArray datagram = msg.toStdString().c_str();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, MCPort);
}

void AConnectionManager::sendNotifyMessage()
{
    QString msg = "NOTIFY * HTTP/1.1\r\n"
                               "CACHE-CONTROL: max-age=1800\r\n"
                               "HOST: "+groupAddress.toString()+":"+QString::number(MCPort)+"\r\n"
                               "LOCATION: http://"+getLocalHostIP()+":41714/altia.xml\r\n"
                               "NT: upnp:rootdevice\r\n"
                               "NTS: ssdp:alive\r\n"
                               "USN: uuid:77777777-ALTIA\r\n"
                               "SERVER: AltiaMediaServer 1.0\r\n\r\n";

    ui->teStatus->append(tr("****Sending NOTIFY Message****\n%1").arg(msg));
    //ui->lwStatus->addItem(tr("Sending NOTIFY Media Renderer\n%1").arg(msg));
    QByteArray datagram = msg.toStdString().c_str();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, MCPort);
}

void AConnectionManager::sendByeByeMessage()
{
    /* Control Point Search */
    QString msg = "NOTIFY * HTTP/1.1\r\n"
                               "HOST: 239.255.255.250:"+QString::number(MCPort)+"\r\n"
                               "NT: upnp:rootdevice\r\n"
                               "NTS: ssdp:byebye\r\n"
                               "USN: uuid:77777777-ALTIA\r\n\r\n";

    ui->teStatus->append(tr("****Sending BYEBYE...****\n%1").arg(msg));
    //ui->lwStatus->addItem(tr("Sending M-SEARCH...\n%1").arg(msg));
    QByteArray datagram = msg.toStdString().c_str();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, MCPort);
}

void AConnectionManager::sendCustomUDPMessage(QString customMessage)
{

    QByteArray datagram = customMessage.toStdString().c_str();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             groupAddress, MCPort);
}


QString AConnectionManager::getLocalHostIP()
{
    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected())
    {
        return socket.localAddress().toString();
    }
    else
    {
        return "no-address";
    }
}



