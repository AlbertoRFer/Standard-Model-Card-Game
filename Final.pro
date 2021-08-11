#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T14:42:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Final
TEMPLATE = app
RC_FILE = icono.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    RoundRectItem.cpp \
    FlipWidget.cpp \
    digitalclock.cpp \
    top10.cpp \
    boton.cpp \
    input_name.cpp \
    new_game.cpp \
    juego_ganado.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    RoundRectItem.h \
    FlipWidget.h \
    digitalclock.h \
    top10.h \
    Tipos_datos.h \
    boton.h \
    input_name.h \
    new_game.h \
    juego_ganado.h \
    help.h

FORMS    += mainwindow.ui \
    top10.ui \
    input_name.ui \
    new_game.ui \
    juego_ganado.ui \
    help.ui

RESOURCES += \
    IMG.qrc \
    Botones.qrc \
    Fondos.qrc
