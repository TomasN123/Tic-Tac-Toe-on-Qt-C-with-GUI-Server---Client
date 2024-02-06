QT       += core gui network\
            multimedia\




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    main.cpp \
    menu.cpp \
    window_play.cpp \
    window_rules.cpp \
    window_scoreboard.cpp

HEADERS += \
    game.h \
    menu.h \
    window_play.h \
    window_rules.h \
    window_scoreboard.h

FORMS += \
    menu.ui \
    window_play.ui \
    window_rules.ui \
    window_scoreboard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
