QT += widgets
QT -= gui

CONFIG += c++11

TARGET = moteur_physique_qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Cercle.cpp \
    collision.cpp \
    Objet.cpp \
    Objet_physique.cpp \
	DisplayUI.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Cercle.h \
    collision.h \
    constantes.h \
    coord.h \
    Info_collision.h \
    Objet.h \
    Objet_physique.h \
    vecteur.h \
	DisplayUI.h



win32:CONFIG(release, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-system-d
else:unix: LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-system

INCLUDEPATH += G:/IDE/Qt/SFML-2.3.2/include
DEPENDPATH += G:/IDE/Qt/SFML-2.3.2/include

win32:CONFIG(release, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-graphics-d
else:unix: LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-graphics

INCLUDEPATH += G:/IDE/Qt/SFML-2.3.2/include
DEPENDPATH += G:/IDE/Qt/SFML-2.3.2/include

win32:CONFIG(release, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-window-d
else:unix: LIBS += -LG:/IDE/Qt/SFML-2.3.2/lib/ -lsfml-window

INCLUDEPATH += G:/IDE/Qt/SFML-2.3.2/include
DEPENDPATH += G:/IDE/Qt/SFML-2.3.2/include
