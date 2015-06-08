#-------------------------------------------------
#
# Project created by QtCreator 2011-05-13T22:58:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlaneShooter
TEMPLATE = app


SOURCES += main.cpp \
    control.cpp \
    application.cpp \
    field.cpp \
    score.cpp

HEADERS  += \
    control.h \
    field.h \
    application.h \
    score.h

RESOURCES += \
    resources.qrc
