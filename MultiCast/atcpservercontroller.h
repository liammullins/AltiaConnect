#ifndef ATCPSERVERCONTROLLER_H
#define ATCPSERVERCONTROLLER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>

#include "project_includes.h"

/* macro to display true or false text in place of the bool */
inline QString bool_cast(const bool b)
{
    return b ? "true" : "false";
}

class ATCPServerController : public QObject
{
    Q_OBJECT

public:
    explicit ATCPServerController(QObject *parent = 0);
    ~ATCPServerController();

    void setupConnection(int port);
    QString albumArtLink;
    QWidget *main_win;
    QString sendClientMessage;


    void setClientMessage(QString msg);
    bool sendCustomTCPMessage(QString message);

    void sendAllCastAdvertisement(/*bool stopped, qint64 duration, qint64 position, bool paused, bool captions*/);

    struct allCastAdvertisement
    {
            bool   p_stopped;
            qint64 p_duration;
            qint64 p_position;
            bool   p_paused;
            bool   p_captions;
    } allCastAdv;

private:



    QTcpServer p_server;
    QTcpSocket *p_client;
    bool firstTimeConnect;
    void processStream(QString rawMessage);

private slots:
    void acceptConnection();
    void startRead();

signals:
    QString servedFile(QString path);

public slots:
};

#endif // ATCPSERVERCONTROLLER_H
