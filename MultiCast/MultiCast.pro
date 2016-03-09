#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T16:34:01
#
#-------------------------------------------------

include(httpserver/httpserver.pri)

QT       += core gui network multimedia multimediawidgets webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MultiCast
TEMPLATE = app

#DEFINES += NETWORK_DEBUG #uncomment to see network debug info

SOURCES += main.cpp \
           mainwindow.cpp \
           altiaupnpcontroller.cpp \
           qcustomplot.cpp \
           aconnectionmanager.cpp \
           amediarenderer.cpp \
           atcpservercontroller.cpp

HEADERS  += mainwindow.h \
            altiaupnpcontroller.h \
            qcustomplot.h \
            aconnectionmanager.h \
            amediarenderer.h \
            atcpservercontroller.h \
            project_includes.h

FORMS    += mainwindow.ui

#INCLUDEPATH += $$PWD/../AutoLiteHMI/altia/altiaGL/libfloat
#INCLUDEPATH += $$PWD/../AutoLiteHMI/altia/windows
#INCLUDEPATH += $$PWD/../AutoLiteHMI/altia

#DEPENDPATH += $$PWD/../AutoLiteHMI

#win32: LIBS += -L$$PWD/../AutoLiteHMI/ -laltiaWinLib /NODEFAULTLIB:LIBCMT
#win32: LIBS += -L$$PWD/../AutoLiteHMI/ -laltiaAPIlibfloat /NODEFAULTLIB:LIBCMT


