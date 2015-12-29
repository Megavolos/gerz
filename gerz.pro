#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T13:15:32
#
#-------------------------------------------------

QT       += core gui


QT += printsupport
TARGET = gerz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    goerzel.cpp \
    qcustomplot.cpp \
    sample.cpp \
    spectrumwindow.cpp \
    grid.cpp

HEADERS  += mainwindow.h \
    goerzel.h \
    qcustomplot.h \
    sample.h \
    spectrumwindow.h \
    grid.h

FORMS    += mainwindow.ui \
    spectrumwindow.ui
