#include <windows.h>
#include "mainwindow.h"

extern MainWindow *main_window;
extern AConnectionManager *connectionManager;

ATCPServerController *tcpServer;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* set our global to this instance - or pass parent */
    main_window = this;
    /* setup ui */
    ui->setupUi(this);
    /* window title */
    setWindowTitle(tr("Multicast Receiver"));
    /* set style sheet */
    setStyleSheet(ui->teStyle->toPlainText());
    /* create new instance of movie player and media components */
    setupPlayer();
    /* start server and update UI */
    ui->pbStartServer->click();
}
void MainWindow::setupPlayer()
{
    /* create a new instance of the connection manager */
    connectionManager = new AConnectionManager(this,ui);
    /* set media */
    player = new QMediaPlayer(ui->mediaView);
    /* create video widget */
    videoWidget = new QVideoWidget(ui->mediaView);
    /* set the output for the player */
    player->setVideoOutput(videoWidget);
    /* create a layout to put the video player in */
    QVBoxLayout *layout = new QVBoxLayout(ui->mediaView);
    /* add the layout to the media view */
    videoWidget->setLayout(layout);
    /* connect to the current position in the media stream and update the horizontal slider (for scrubbing)  */
    connect(player, SIGNAL(positionChanged(qint64)),
                   this,    SLOT(mediaPositionChanged(qint64)));
    /* hook up to the buffering signal to drive the buffering progress bar */
    connect(player, SIGNAL(bufferStatusChanged(int)),
                   this,    SLOT(checkMediaBufferStatus(int)));
    /* init finding track position flag */
    scrubbingMedia = false;
    /* Show the video widget */
    videoWidget->show();
}
MainWindow::~MainWindow()
{
    /* tell the network devices goodbye */
    connectionManager->sendByeByeMessage();
    /* clean up connectionManager */
    delete connectionManager;
    delete videoWidget;
    delete player;
    delete ui;
}

void MainWindow::checkMediaBufferStatus(int status)
{
    qDebug() << "buffering status: "<< status;
    /* update buffer progress bar */
    ui->pbBuffer->setValue(status);
    /* if it's less than 50, buffer and don't play */
    if (status < 50)
    {
        player->pause();
    }
    else
    {
        player->play();
    }
}

void MainWindow::mediaPositionChanged(qint64 pos)
{
    /* scrubbing and redefining current position. */
    if(scrubbingMedia)
    {
        return;
    }
    /* update track position */
    ui->lblLength->setText(QString::number(pos)+" / "+QString::number(player->duration()));
    /* set the maximum */
    ui->hsPosition->setMaximum(player->duration());
    /* set the current track position on the horizontal  */
    ui->hsPosition->setValue(pos);
    /* update  duration */
    tcpServer->allCastAdv.p_duration = player->duration();
    /* update/scrub position */
    tcpServer->allCastAdv.p_position = pos;
    //player->play();
}

void MainWindow::on_pushButton_clicked()
{
    connectionManager->sendDiscoverMessage();
}

void MainWindow::on_pushButton_2_clicked()
{
    connectionManager->sendNotifyMessage();
}

void MainWindow::on_pushButton_5_clicked()
{
    connectionManager->sendByeByeMessage();
}

void MainWindow::on_pbHostServer_clicked(bool checked)
{

}

void MainWindow::on_pushButton_3_clicked()
{

    QPixmap* pixmap = new QPixmap("ship_cargo_vessel_no_rotation.png");
    QTransform transform;
    QTransform trans = transform.rotate(45);
    pixmap = new QPixmap(pixmap->scaled(sqrt(pixmap->size().width()), sqrt(pixmap->size().height())));
    QPixmap *transPixmap = new QPixmap(pixmap->transformed(trans));
    //server = new ATCPServercontroller(this);

    //QApplication::desktop()->cursor().setPos(1,1);
    //mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
}

void MainWindow::setPlayerPosition(int position)
{
    player->setPosition(tcpServer->allCastAdv.p_position);
}

void MainWindow::playMedia(QString path)
{
    try
    {
        if (path.indexOf("allcast.jpg")>0)
        {
            videoWidget->setMinimumHeight(72);
            videoWidget->setMinimumWidth(72);
            path = "altialogo.png";
        }
        else
        {
            videoWidget->setMinimumWidth(ui->tabHome->width());
            videoWidget->setMinimumHeight(ui->tabHome->height());
        }
        /* problematic method (getting album art and playing track this way) */
           //if (!tcpServer->albumArtLink.isEmpty())
                 //ui->pbPlay->click();
        /* set scrub information */
        ui->hsPosition->setMaximum(player->duration());
        ui->lblLength->setText(QString::number(player->duration()));
        /* set tcpServer variables for cast message */
        tcpServer->allCastAdv.p_stopped = false;
        tcpServer->allCastAdv.p_duration = player->duration();
        tcpServer->allCastAdv.p_position = -1;
        tcpServer->allCastAdv.p_paused = false;
        tcpServer->allCastAdv.p_captions = false;
        /* set the play button to play */
        ui->pbPlayPause->setText("▮▮");
        ui->pbPlayPause->setChecked(true);
        /* open up the media provided by service, parse, and get media metrics */
        player->setMedia(QUrl(path));
        player->setVolume(ui->hsVolume->value());
        player->play();
        /* kick things off with an advertisement */
        tcpServer->sendAllCastAdvertisement();
        qDebug() << "\nplaying... "<< path <<"\n";
    }
    catch (...)
    {
        qDebug() << "issue..";
    }

}

void MainWindow::on_pbPlay_clicked()
{

    QNetworkAccessManager *m_netwManager = new QNetworkAccessManager(this);

    connect(m_netwManager, SIGNAL(finished(QNetworkReply*)),
                   this,                       SLOT(slot_netwManagerFinished(QNetworkReply*)));

    QUrl url(tcpServer->albumArtLink);
    QNetworkRequest request(url);
    m_netwManager->get(request);

}

void MainWindow::on_hsVolume_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::slot_netwManagerFinished(QNetworkReply *reply)
{

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error in " << reply->url() << ":" << reply->errorString();
        return;
    }

    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    ui->lblAlbumArt->setPixmap(pixmap);
    ui->lblAlbumArt->setScaledContents(true);
}
void MainWindow::on_hsBrightness_valueChanged(int value)
{
    videoWidget->setBrightness(value);
}

void MainWindow::on_hsContrast_sliderMoved(int position)
{
    videoWidget->setContrast(position);
    //qDebug() << "buffer..." << player->duration();
}

void MainWindow::on_hsSaturation_sliderMoved(int position)
{
    videoWidget->setSaturation(position);
}
void MainWindow::on_hsPosition_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_pbPlayPause_clicked(bool checked)
{
   /* if(!checked)
    {
        ui->pbPlayPause->setText("►");
        tcpServer->p_paused = false;
        player->play();
    }
    else
    {
        ui->pbPlayPause->setText("▮▮");
        tcpServer->p_paused = true;
        player->pause();
    }*/
}
void MainWindow::on_pbPlayPause_toggled(bool checked)
{
    if(checked)
    {
        ui->pbPlayPause->setText("▮▮");
        tcpServer->allCastAdv.p_paused = false;
        player->play();
        /* make sure everyone knows */
        tcpServer->sendAllCastAdvertisement();
    }
    else
    {
        ui->pbPlayPause->setText("►");
         tcpServer->allCastAdv.p_paused = true;
        player->pause();
         /* make sure everyone knows */
         tcpServer->sendAllCastAdvertisement();
    }
}

void MainWindow::on_hsPosition_sliderPressed()
{
    if(player->state() == player->PlayingState)
    {
        //player->pause();
    }
    scrubbingMedia = true;
}

void MainWindow::on_hsPosition_sliderReleased()
{
   // player->play();
    scrubbingMedia = false;
}

void MainWindow::on_cbOpenHomeMode_clicked(bool checked)
{
    if(checked)
    {
        ui->lblOpenHomeMode->setText("OpenHome &nbsp;<span style='color:red;font-weight:bold'>  On </span>");
    }
    else
    {
         ui->lblOpenHomeMode->setText("OpenHome &nbsp;<span style='color:#424242;font-weight:bold'>  Off </span>");
    }

}

void MainWindow::on_pbStartServer_clicked(bool checked)
{

    if (checked)
    {
        if (ui->cbOpenHomeMode->isChecked() )
        {
            connectionManager->setPort(1900);
            qDebug() << "port "+1900;
        }
        else
        {
            connectionManager->setPort(53515);
            qDebug() << "port "<<53515;
        }
        /* start the http server */
        connectionManager->startHTTPServer();
        /* start the UPnP server */
        connectionManager->startUPNPServer();

        ui->teStatus->append("----------\nStarted listening for multicast messages on\n----------");
        ui->lblRendererStatus->setText("Renderer &nbsp;&nbsp;<span style='color:red;font-weight:bold'>  On </span>");
    }
    else
    {
        connectionManager->stopHTTPServer();
        ui->teStatus->append("Left Group");
        ui->lblRendererStatus->setText("Renderer &nbsp;&nbsp;<span style='color:#424242;font-weight:bold'>  Off </span>");
    }

}
