/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabHome;
    QVBoxLayout *verticalLayout_4;
    QFrame *mediaView;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pbPlayPause;
    QSpacerItem *horizontalSpacer_2;
    QSlider *hsPosition;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTableWidget *twIPHosts;
    QTextEdit *teStatus;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QPushButton *pbStartServer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pbPlay;
    QPushButton *pushButton_3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *lblLength;
    QComboBox *cbMCPort;
    QPushButton *pushButton;
    QProgressBar *pbBuffer;
    QLabel *lblRendererStatus;
    QLabel *lblRendererStatus_2;
    QLabel *lblRendererStatus_3;
    QPushButton *cbOpenHomeMode;
    QLabel *lblOpenHomeMode;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblAlbumArt;
    QLabel *netTraffic;
    QSpacerItem *verticalSpacer;
    QFrame *frame_5;
    QSlider *hsVolume;
    QLabel *label;
    QSlider *hsBrightness;
    QLabel *label_6;
    QSlider *hsContrast;
    QLabel *label_7;
    QSlider *hsSaturation;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *teStyle;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1163, 936);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabHome = new QWidget();
        tabHome->setObjectName(QStringLiteral("tabHome"));
        verticalLayout_4 = new QVBoxLayout(tabHome);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        mediaView = new QFrame(tabHome);
        mediaView->setObjectName(QStringLiteral("mediaView"));
        mediaView->setMinimumSize(QSize(500, 500));
        mediaView->setFrameShape(QFrame::StyledPanel);
        mediaView->setFrameShadow(QFrame::Raised);

        verticalLayout_4->addWidget(mediaView);

        frame_6 = new QFrame(tabHome);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setMinimumSize(QSize(0, 55));
        frame_6->setMaximumSize(QSize(16777215, 55));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pbPlayPause = new QPushButton(frame_6);
        pbPlayPause->setObjectName(QStringLiteral("pbPlayPause"));
        pbPlayPause->setMinimumSize(QSize(48, 48));
        pbPlayPause->setMaximumSize(QSize(48, 48));
        pbPlayPause->setCheckable(true);

        horizontalLayout_3->addWidget(pbPlayPause);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        hsPosition = new QSlider(frame_6);
        hsPosition->setObjectName(QStringLiteral("hsPosition"));
        hsPosition->setValue(0);
        hsPosition->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hsPosition);


        verticalLayout_4->addWidget(frame_6);

        tabWidget->addTab(tabHome, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame = new QFrame(tab_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        twIPHosts = new QTableWidget(frame);
        if (twIPHosts->columnCount() < 2)
            twIPHosts->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twIPHosts->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twIPHosts->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        twIPHosts->setObjectName(QStringLiteral("twIPHosts"));
        twIPHosts->horizontalHeader()->setDefaultSectionSize(200);
        twIPHosts->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        twIPHosts->horizontalHeader()->setStretchLastSection(true);
        twIPHosts->verticalHeader()->setStretchLastSection(false);

        horizontalLayout->addWidget(twIPHosts);

        teStatus = new QTextEdit(frame);
        teStatus->setObjectName(QStringLiteral("teStatus"));
        teStatus->setMaximumSize(QSize(375, 16777215));

        horizontalLayout->addWidget(teStatus);


        verticalLayout_3->addWidget(frame);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        horizontalLayout_4 = new QHBoxLayout(tab_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        frame_2 = new QFrame(tab_4);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(275, 0));
        frame_2->setMaximumSize(QSize(230, 16777215));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(0, 500));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        pbStartServer = new QPushButton(frame_3);
        pbStartServer->setObjectName(QStringLiteral("pbStartServer"));
        pbStartServer->setGeometry(QRect(0, 40, 104, 48));
        pbStartServer->setCheckable(true);
        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 250, 131, 41));
        pushButton_5 = new QPushButton(frame_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(138, 250, 121, 41));
        pbPlay = new QPushButton(frame_3);
        pbPlay->setObjectName(QStringLiteral("pbPlay"));
        pbPlay->setGeometry(QRect(110, 750, 111, 28));
        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(12, 750, 91, 28));
        pushButton_8 = new QPushButton(frame_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(120, 680, 71, 41));
        pushButton_9 = new QPushButton(frame_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(40, 680, 71, 41));
        lblLength = new QLabel(frame_3);
        lblLength->setObjectName(QStringLiteral("lblLength"));
        lblLength->setGeometry(QRect(100, 335, 141, 31));
        lblLength->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cbMCPort = new QComboBox(frame_3);
        cbMCPort->setObjectName(QStringLiteral("cbMCPort"));
        cbMCPort->setGeometry(QRect(20, 780, 111, 31));
        cbMCPort->setEditable(true);
        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 700, 101, 41));
        pbBuffer = new QProgressBar(frame_3);
        pbBuffer->setObjectName(QStringLiteral("pbBuffer"));
        pbBuffer->setGeometry(QRect(0, 370, 241, 23));
        pbBuffer->setValue(0);
        pbBuffer->setTextVisible(false);
        lblRendererStatus = new QLabel(frame_3);
        lblRendererStatus->setObjectName(QStringLiteral("lblRendererStatus"));
        lblRendererStatus->setGeometry(QRect(110, 42, 161, 41));
        lblRendererStatus_2 = new QLabel(frame_3);
        lblRendererStatus_2->setObjectName(QStringLiteral("lblRendererStatus_2"));
        lblRendererStatus_2->setGeometry(QRect(0, 210, 211, 41));
        lblRendererStatus_3 = new QLabel(frame_3);
        lblRendererStatus_3->setObjectName(QStringLiteral("lblRendererStatus_3"));
        lblRendererStatus_3->setGeometry(QRect(0, 330, 201, 41));
        cbOpenHomeMode = new QPushButton(frame_3);
        cbOpenHomeMode->setObjectName(QStringLiteral("cbOpenHomeMode"));
        cbOpenHomeMode->setGeometry(QRect(0, 110, 104, 48));
        cbOpenHomeMode->setCheckable(true);
        lblOpenHomeMode = new QLabel(frame_3);
        lblOpenHomeMode->setObjectName(QStringLiteral("lblOpenHomeMode"));
        lblOpenHomeMode->setGeometry(QRect(110, 112, 161, 41));
        lblRendererStatus_3->raise();
        pbStartServer->raise();
        pushButton_2->raise();
        pushButton_5->raise();
        pbPlay->raise();
        pushButton_3->raise();
        pushButton_8->raise();
        pushButton_9->raise();
        lblLength->raise();
        cbMCPort->raise();
        pushButton->raise();
        pbBuffer->raise();
        lblRendererStatus->raise();
        lblRendererStatus_2->raise();
        cbOpenHomeMode->raise();
        lblOpenHomeMode->raise();

        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setMinimumSize(QSize(0, 200));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_4);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        lblAlbumArt = new QLabel(frame_4);
        lblAlbumArt->setObjectName(QStringLiteral("lblAlbumArt"));
        lblAlbumArt->setMinimumSize(QSize(250, 150));
        lblAlbumArt->setMaximumSize(QSize(250, 200));

        verticalLayout_5->addWidget(lblAlbumArt);

        netTraffic = new QLabel(frame_4);
        netTraffic->setObjectName(QStringLiteral("netTraffic"));

        verticalLayout_5->addWidget(netTraffic);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setMinimumSize(QSize(0, 300));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        hsVolume = new QSlider(frame_5);
        hsVolume->setObjectName(QStringLiteral("hsVolume"));
        hsVolume->setGeometry(QRect(10, 70, 211, 22));
        hsVolume->setValue(20);
        hsVolume->setOrientation(Qt::Horizontal);
        label = new QLabel(frame_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 111, 21));
        hsBrightness = new QSlider(frame_5);
        hsBrightness->setObjectName(QStringLiteral("hsBrightness"));
        hsBrightness->setGeometry(QRect(10, 130, 211, 22));
        hsBrightness->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(frame_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 100, 111, 21));
        hsContrast = new QSlider(frame_5);
        hsContrast->setObjectName(QStringLiteral("hsContrast"));
        hsContrast->setGeometry(QRect(10, 190, 211, 22));
        hsContrast->setOrientation(Qt::Horizontal);
        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 160, 111, 21));
        hsSaturation = new QSlider(frame_5);
        hsSaturation->setObjectName(QStringLiteral("hsSaturation"));
        hsSaturation->setGeometry(QRect(10, 250, 211, 22));
        hsSaturation->setOrientation(Qt::Horizontal);
        label_8 = new QLabel(frame_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 220, 111, 21));

        verticalLayout_5->addWidget(frame_5);


        verticalLayout->addWidget(frame_4);


        horizontalLayout_4->addWidget(frame_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        teStyle = new QPlainTextEdit(tab_4);
        teStyle->setObjectName(QStringLiteral("teStyle"));
        teStyle->setMaximumSize(QSize(0, 16777215));

        horizontalLayout_4->addWidget(teStyle);

        tabWidget->addTab(tab_4, QString());

        horizontalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pbPlayPause->setText(QApplication::translate("MainWindow", "\342\226\272", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabHome), QApplication::translate("MainWindow", "   Altia Connect Renderer   ", 0));
        QTableWidgetItem *___qtablewidgetitem = twIPHosts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Server Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = twIPHosts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "IP Address", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Network Status", 0));
        pbStartServer->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "Notify", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Leave", 0));
        pbPlay->setText(QApplication::translate("MainWindow", "Play", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Render", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "Stop", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "Play", 0));
        lblLength->setText(QApplication::translate("MainWindow", "--:--:--", 0));
        cbMCPort->clear();
        cbMCPort->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1900", 0)
         << QApplication::translate("MainWindow", "53515", 0)
        );
        pushButton->setText(QApplication::translate("MainWindow", "Discover", 0));
        lblRendererStatus->setText(QApplication::translate("MainWindow", "Renderer On", 0));
        lblRendererStatus_2->setText(QApplication::translate("MainWindow", "UPnP Advertisements", 0));
        lblRendererStatus_3->setText(QApplication::translate("MainWindow", "Buffer Status", 0));
        cbOpenHomeMode->setText(QString());
        lblOpenHomeMode->setText(QApplication::translate("MainWindow", "OpenHome &nbsp;<span style='color:#424242;font-weight:bold'>  Off </span>", 0));
        lblAlbumArt->setText(QString());
        netTraffic->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Volume", 0));
        label_6->setText(QApplication::translate("MainWindow", "Brightness", 0));
        label_7->setText(QApplication::translate("MainWindow", "Contrast", 0));
        label_8->setText(QApplication::translate("MainWindow", "Saturation", 0));
        teStyle->setPlainText(QApplication::translate("MainWindow", "#frFrameRate\n"
"{\n"
"    background: rgba(0,0,0,.20);\n"
"}\n"
"#pbPlayPause:checked\n"
"{\n"
"    background : qlineargradient(x1: 0.3, y1: 0, x2: 0, y2: 0,\n"
"    stop: 0 #121212, stop: 0 #223500,\n"
"    stop: 0 #121212, stop: 0 #235887);\n"
"    border:1px outset #00B2EE;\n"
"    padding-left:11px;\n"
"    color : #11ccFF;\n"
"    outline : none;\n"
"}\n"
"\n"
"#cbOpenHomeMode\n"
"{\n"
"     border:none;\n"
"     width:130px;\n"
"     height: 60px;\n"
"     background: url(style/images/checkbox_off_over.png);\n"
"}\n"
"#cbOpenHomeMode:checked\n"
"{\n"
"    border:none;\n"
"     background: url(style/images/checkbox_on.png);\n"
"    \n"
"}\n"
"#pbStartServer\n"
"{\n"
"     border:none;\n"
"     width:130px;\n"
"     height: 60px;\n"
"     background: url(style/images/checkbox_off_over.png);\n"
"}\n"
"#pbStartServer:checked\n"
"{\n"
"     border:none;\n"
"     background: url(style/images/checkbox_on.png);\n"
"    \n"
"}\n"
"\n"
"#netTraffic\n"
"{\n"
"	background: url(style/images/connect.png) no-repeat;\n"
""
                        "}\n"
"#noNetTraffic\n"
"{\n"
"	background: url(style/images/sigoffsss.png) no-repeat;\n"
"}\n"
"QGraphicsView\n"
"{\n"
"    background: rgba(12,34,56,20);\n"
"    font-family : \"Consolas\";\n"
"    border: 1px inset #272727;\n"
"    color : white;\n"
"    border-radius: 2px;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"\n"
"QGroupBox\n"
"{\n"
"	color:white;\n"
"	font-size:18px;\n"
"	/*border:1px solid #4f4f4f;*/\n"
"	border:none;\n"
"	border-radius: 3px;\n"
"    font-family : \"Consolas\";\n"
"}\n"
"\n"
"QTableWidget\n"
"{\n"
"    background : white;\n"
"    color      : black;\n"
"    \n"
"    outline    : none;\n"
"    \n"
"    \n"
"}\n"
"QTableWidget::item:focus\n"
"{\n"
"    background-color: qlineargradient(x1: 0, y1: 0.5, x2: 0, y2: 0.5,\n"
"    stop: 0 #17d9ff, stop: 1 white);\n"
"    border     : 1px solid #85f9ff;\n"
"    outline : none;\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    \n"
"    background: rgba(12,34,56,0);\n"
"    font-family : \"Consolas\";\n"
"    padding-left: 7px;\n"
"    border: 1px inset #27"
                        "2727;\n"
"    color : white;\n"
"    border-radius: 1px;\n"
"    font-size: 18px;\n"
"    \n"
"}\n"
"\n"
"QToolBox\n"
"{\n"
"    background: rgba(12,34,56,0);\n"
"    font-family : \"Consolas\";\n"
"    padding: 15px;\n"
"    border: 1px inset #272727;\n"
"    color : white;\n"
"    border-radius: 5px;\n"
"    font-size: 16px;\n"
"    \n"
"}\n"
"\n"
"\n"
"QToolBox::tab \n"
"{\n"
"    background:rgba(0, 0, 0, .78);\n"
"    border: 1px inset #272727;\n"
"    color : white;\n"
"    font-size: 20px;\n"
"    \n"
"}\n"
"\n"
"QToolBox::tab:selected \n"
"{\n"
"    background:rgba(0, 0, 0, .78);\n"
"    font-weight:bold;\n"
"    color:#cf0003;\n"
"    text-align:center;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"/**\n"
"* Radiobutton style\n"
"*/\n"
"QRadioButton\n"
"{\n"
"    font-size: 16px;\n"
"    color : white;\n"
"    height: 32px;\n"
"}\n"
"QRadioButton::indicator::checked \n"
"{\n"
"    image: url(style/images/radiobutton_red_active.png);\n"
"}\n"
"QRadioButton::indicator \n"
"{\n"
"    image: url(style/images/rad"
                        "iobutton_red.png);\n"
"    color : #ffffff;\n"
"    font-size:16px;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"QToolTip\n"
"{\n"
"    color: #e4f3ff;\n"
"    background-repeat:no-repeat;\n"
"    background-position:center;\n"
"    background-color:rgba(0, 0, 0, .40);\n"
"    border:none;\n"
"    border-radius:2px;\n"
"}\n"
"\n"
"QMainWindow\n"
"{\n"
"    background-color:#000;\n"
"    border:0px inset #000;\n"
"    border-image: url(style/images/bg_blue_rust.jpg) no-repeat ;\n"
"    background-position: top center;\n"
"    font-family : \"Consolas\";\n"
"}\n"
"\n"
"/* Progress bar style */\n"
"QProgressBar \n"
"{\n"
"    border: 1px inset #202020;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #e51937;\n"
"    width: 20px;\n"
"}\n"
"\n"
"/* Label - default style */\n"
"QLabel\n"
"{\n"
"    font-family:\"arial\";\n"
"    font-size:16px;\n"
"    color:#ffffff;\n"
"}\n"
"\n"
"\n"
"/* Checkbox */\n"
"QCheckBox\n"
"{\n"
"    spacing: 5px;\n"
"    font-family: \"arial\";\n"
"    fo"
                        "nt-size : 16px;\n"
"    padding-left : 5px;\n"
"    text-align: left;\n"
"    color : #e9e9e9;\n"
"}\n"
"\n"
"QCheckBox::indicator \n"
"{\n"
"    width: 40px;\n"
"    height: 38px;\n"
"    color : #e9e9e9;\n"
"}\n"
"QCheckBox::indicator:hover\n"
"{\n"
"    image: url(style/images/cbLB1.png);\n"
"    color : #e9e9e9;     \n"
"}\n"
"QCheckBox::indicator:unchecked\n"
"{\n"
"    image: url(style/images/cbLB1.png);\n"
"    color:#ffffff;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked \n"
"{\n"
"    image: url(style/images/cbLB_checked2.png);\n"
"    color : #e9e9e9;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:pressed \n"
"{\n"
"    image: url(style/images/cbLB1.png);\n"
"}\n"
"QCheckBox::indicator:disabled \n"
"{\n"
"    image: url(style/images/cbLB1.png);\n"
"    color : #f1f1f1;\n"
"}\n"
"/*\n"
"\n"
"\n"
"\n"
"QCheckBox::indicator:unchecked:pressed {\n"
"    image: url(style/images/checkbox_unchecked_pressed.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:hover {\n"
"    image: url(style/images/checkbox_in"
                        "determinate_hover.png);\n"
"}\n"
"QCheckBox::indicator:indeterminate:pressed {\n"
"    image: url(style/images/checkbox_indeterminate_pressed.png);\n"
"}\n"
"*/\n"
"\n"
"QPushButton\n"
"{\n"
"    background-color:rgba(0, 0, 0, .30);\n"
"    border-radius:3px;\n"
"    color:#b3b3b3;\n"
"    font-size:10pt;   \n"
"    font-family : \"Consolas\"; \n"
"    padding:8px;\n"
"    border:1px inset  rgba(255,255,255,.08);\n"
"    \n"
"}\n"
"QPushButton:hover\n"
"{\n"
"    background : #235887;\n"
"    color  : #ffffff;\n"
"    border : 0px solid #b2cdff;\n"
"    \n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background-color:#42a7ff;\n"
"    border: 1px solid #72fff6;\n"
"    \n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"    \n"
"    background : qlineargradient(x1: 0.3, y1: 0, x2: 0, y2: 0,\n"
"    stop: 0 #121212, stop: 0 #3183a6,\n"
"    stop: 0 #121212, stop: 0 #3183a6);\n"
"    border:1px outset #fff;\n"
"    color : #ffffff;\n"
"    padding-right:11px;\n"
"    outline : none;\n"
"    \n"
"}\n"
"QPushButton:focus\n"
""
                        "{\n"
"    outline : none;\n"
"}\n"
"QTabWidget::pane \n"
"{ /* The tab widget frame */\n"
"    border:1px solid #eaeaea;\n"
"    \n"
"}\n"
"\n"
"QTabWidget::tab-bar\n"
"{\n"
"    \n"
"    left: 0px; /* move to the right by 5px */\n"
"}\n"
"\n"
"\n"
"\n"
"QListWidget\n"
"{\n"
"    background: #1b1b1b;\n"
"	border: 1px solid black;\n"
"	border-radius: 6px;\n"
" 	show-decoration-selected: 1;\n"
"	padding:1px;\n"
"	font-family: \"Arial\";\n"
"	border-left:1px solid #717171;\n"
"	outline:none;\n"
"	color : #f1f1f1;\n"
"}\n"
"\n"
"QListWidget:item:alternate \n"
"{\n"
"    background: #222222;\n"
"}\n"
"\n"
"QListWidget:item:selected \n"
"{\n"
"    \n"
"	color:#ffffff;\n"
"	outline: none;\n"
"	\n"
"}\n"
"\n"
"QListWidget:item:selected:!active \n"
"{\n"
"    background: #2e2e2e;\n"
"	color: #ffffff;\n"
"}\n"
"\n"
"QListWidget:item:selected:active \n"
"{\n"
"    background: #2a2a2a;\n"
"	color: #f1f1f1;\n"
"}\n"
"QListWidget:item:hover \n"
"{\n"
"    background: #2f2f2f;\n"
"	text-decoration: underline;\n"
"	color: whi"
                        "te;\n"
"}\n"
"QListWidget:item\n"
"{\n"
"    height: 50px;\n"
"	background: #414141;\n"
"	padding-left: 5px;\n"
"	border-radius: 0px;\n"
"	color : #cacaca;\n"
"	outline:none;\n"
"}\n"
"\n"
"\n"
"/* QSlider style */\n"
"\n"
"QSlider::groove:horizontal\n"
"{\n"
"    border: 1px solid #dedede;\n"
"    height: 16px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    border: 1px solid #393939;\n"
"    background: #0a0a0a;\n"
"}\n"
"QSlider::handle:horizontal \n"
"{\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:0, stop:0 #3fbeff, stop:1 #3fbeff);\n"
"    border: 1px outset #09a1ee;\n"
"    width: 42px;\n"
"    margin: 0px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 2px;\n"
"}\n"
"QSlider::groove:vertical \n"
"{\n"
"    background: red;\n"
"    position: absolute; /* absolutely position 4px from the left and right of the widget. setting margins on the widget should wo"
                        "rk too... */\n"
"    left: 4px; \n"
"    right: 4px;\n"
"}\n"
"QSlider::handle:vertical \n"
"{\n"
"    height: 10px;\n"
"    background: green;\n"
"    margin: 0 -4px; /* expand outside the groove */\n"
"}\n"
"QSlider::add-page:vertical \n"
"{\n"
"    background: black;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical \n"
"{\n"
"    margin-top:50px;\n"
"    background: yellow;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"/*  QTab */\n"
"QTabWidget::pane \n"
"{ /* The tab widget frame */\n"
"    border-top : none;\n"
"    border-left : none;\n"
"    border-bottom : 1px outset #555555;\n"
"    border-right : none;\n"
"    background-color:rgba(0, 0, 0, .70);\n"
"    \n"
"}\n"
"\n"
"QTabWidget::tab-bar \n"
"{\n"
"    left: 0px; /* move to the right by 5px */\n"
"    background-color:black;\n"
"}\n"
"\n"
"QTabBar::tab\n"
"{\n"
"    /*\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"    stop: 0 #121212, stop: 0.4 #121212,\n"
"    stop: 0.5 #000, stop: 1.0 #000);\n"
"    border: 0px solid #cfcfcf;\n"
"    */\n"
"    b"
                        "ackground-color:rgba(0, 0, 0, .30);  \n"
"    border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"    min-width: 150px;\n"
"    max-height:12px;\n"
"	min-height:12px;\n"
"    padding:12px;\n"
"    font-family: \"Consolas\";\n"
"    font-size: 12px;\n"
"	font-weight:normal;\n"
"    color:#6b6b6b;\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    /*\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"    stop: 0 #515151, stop: 0.4 #515151,\n"
"    stop: 0.5 #4e4e4e, stop: 1.0 #4e4e4e);  \n"
"    */\n"
"    \n"
"    background-color:rgba(0, 0, 0, .70);  \n"
"}\n"
"\n"
"QTabBar::tab:hover \n"
"{\n"
"    /*\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"    stop: 0 #272727, stop: 0.4 #272727,\n"
"    stop: 0.5 #272727, stop: 1.0 #272727);\n"
"   \n"
"    background-color:rgba(0, 0, 0, .50);   */\n"
"    border-bottom:1px inset #255681;\n"
"    color: #dddddd;\n"
"	font-weight:bold;\n"
"	\n"
"}\n"
"\n"
"QTabBar::tab:selected \n"
"{\n"
"    \n"
"    border-bottom: 0px "
                        "inset #565656; /* same as pane color */\n"
"    /* expand/overlap to the left and right by 4px */\n"
"    color: #49aaff;\n"
"	\n"
"}\n"
"\n"
"QTabBar::tab:first:selected \n"
"{\n"
"    margin-left: 0; /* the first selected tab has nothing to overlap with on the left */\n"
"}\n"
"\n"
"QTabBar::tab:last:selected \n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"}\n"
"\n"
"QTabBar::tab:only-one \n"
"{\n"
"    margin: 0; /* if there is only one tab, we don't want overlapping margins */\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"    border: 1px solid #393939;\n"
"    background: #0a0a0a;\n"
"    width: 17px;\n"
"    margin: 22px 0 22px 0;\n"
"	\n"
"}\n"
"\n"
"\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,\n"
"    stop: 0 #3a3a3a, stop: 0.4 #616161,\n"
"    stop: 0.5 #616161, stop: 1.0 #3a3a3a);\n"
"    border-radius:1px;\n"
"    min-height: 20px;\n"
"}\n"
"QScrollBar::handle:vertical:pressed\n"
""
                        "{\n"
"    border: 1px inset #1f1f1f;\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,\n"
"    stop: 0 #4a4a4a, stop: 0.4 #616161,\n"
"    stop: 0.5 #616161, stop: 1.0 #4a4a4a);\n"
"}\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"    \n"
"    height: 20px;\n"
"    subcontrol-position: bottom;\n"
"    subcontrol-origin: margin;\n"
"	border-radius: 2px;\n"
"    background:#5c5c5c;\n"
"\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"    height: 20px;\n"
"    border: none;\n"
"	border-radius: 2px;\n"
"    background:#5c5c5c;\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical:pressed \n"
"{\n"
"    background: #1f1f1f;\n"
"    border: 1px solid black;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical:pressed \n"
"{\n"
"    background: #1f1f1f;\n"
"    border: 1px solid black;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical \n"
"{\n"
"  \n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertic"
                        "al \n"
"{\n"
"    background: none;\n"
"}", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
