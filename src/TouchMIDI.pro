#-------------------------------------------------
#
# Project created by QtCreator 2011-10-01T23:34:52
#
#-------------------------------------------------

QT       += core gui
QT       += svg

TARGET = TouchMIDI
TEMPLATE = app

SOURCES += main.cpp\
    aboutwindow.cpp \
    processthread.cpp \
    vpiano.cpp \
    synclient.cpp \
    RtMidi.cpp \
	touchmidi.cpp

HEADERS  += aboutwindow.h \
    processthread.h \
    vpiano.h \
    synclient.h \
    RtMidi.h \
    RtError.h \
    mididefs.h \
    touchmidi.h

FORMS    += aboutwindow.ui \
    touchmidi.ui

LIBS += -L/alsa/ -lpthread -lasound -lX11 -lXi
