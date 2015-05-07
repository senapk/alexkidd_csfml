TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
INCLUDEPATH += /usr/lib/

SOURCES += \
    game.c \
    aluno.c \
    csf.c

HEADERS += \
    aluno.h \
    csf.h

