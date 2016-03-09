#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "project_includes.h"


#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>


//#include <altia.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupPlayer();

    void setPlayerPosition(int position);


    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;

    Ui::MainWindow *ui;
    bool changingMovieSliderPosition;

private:


    qint64 newSliderPosition;
    bool    scrubbingMedia;
public slots:

    void playMedia(QString path);

    void checkMediaBufferStatus(int status);

private slots:

    void on_pbPlayPause_toggled(bool checked);

    void slot_netwManagerFinished(QNetworkReply *reply);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pbHostServer_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_pbPlay_clicked();

    void on_hsVolume_sliderMoved(int position);

    void on_hsBrightness_valueChanged(int value);

    void on_hsContrast_sliderMoved(int position);

    void on_hsSaturation_sliderMoved(int position);

    void on_hsPosition_sliderMoved(int position);

    void mediaPositionChanged(qint64 pos);

    void on_pbPlayPause_clicked(bool checked);

    void on_hsPosition_sliderPressed();

    void on_hsPosition_sliderReleased();

    void on_cbOpenHomeMode_clicked(bool checked);

    void on_pbStartServer_clicked(bool checked);
};

#endif // MAINWINDOW_H
