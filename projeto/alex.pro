TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c99

LIBS += -L/usr/lib -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
INCLUDEPATH += /usr/lib/

SOURCES += \
    game.c \
    prof.c \
    csf.c

HEADERS += \
    prof.h \
    csf.h

