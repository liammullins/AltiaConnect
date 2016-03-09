#ifndef ACONNECTIONMANAGER_H
#define ACONNECTIONMANAGER_H

#include <QObject>
#include <QUdpSocket>

#include "project_includes.h"


namespace Ui {
class MainWindow;
}

class AConnectionManager : QObject
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;


public://functions
    explicit AConnectionManager(QObject *parent = 0, Ui::MainWindow *_ui = NULL);
    ~AConnectionManager();

    void startHTTPServer();
    void stopHTTPServer();
    void sendNotifyMessage();
    void sendByeByeMessage();
    void sendDiscoverMessage();
    QString getLocalHostIP();
    void setPort(int port);
    void setGroupIP(QString address);
    void setTrafficStatus(bool traffic);
    void startUPNPServer();
    void addIPToTable(QString ip, QString serverName);
    void clearTable();
    void removeRow(int row);
    void updateRow(int row, QString ip, QString serverName);

public://variables
    /* default should be 1900 */
    unsigned int MCPort = 53515;
    QUdpSocket *udpSocket;
    QHostAddress senderIP;
    quint16 senderPort;

    void sendCustomUDPMessage(QString customMessage);

signals:

public slots:

    void processPendingDatagrams();

private slots:

private:
    /** Controller for static files */
    //StaticFileController* staticFileController;
    //ATCPServerController *tcpServer;
    QHostAddress groupAddress;
    QString configFileName;
    HttpListener *http_listener;
    //ATCPServerController *tcpServer;
};

#endif // ACONNECTIONMANAGER_H
