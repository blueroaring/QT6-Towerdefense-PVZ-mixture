QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caltrop.cpp \
    cherrybomb.cpp \
    chomper.cpp \
    choosesave.cpp \
    commonzombie.cpp \
    enemy.cpp \
    footballzombie.cpp \
    game.cpp \
    help.cpp \
    main.cpp \
    mainwindow.cpp \
    maps.cpp \
    mapway.cpp \
    menu.cpp \
    pea.cpp \
    peashooter.cpp \
    repeater.cpp \
    shop.cpp \
    shopcard.cpp \
    shovel.cpp \
    snowpea.cpp \
    tower.cpp \
    trashzombie.cpp \
    wallnut.cpp \
    way.cpp \
    words.cpp

HEADERS += \
    caltrop.h \
    cherrybomb.h \
    chomper.h \
    choosesave.h \
    commonzombie.h \
    enemy.h \
    footballzombie.h \
    game.h \
    help.h \
    mainwindow.h \
    maps.h \
    mapway.h \
    menu.h \
    pea.h \
    peashooter.h \
    repeater.h \
    reused.h \
    shop.h \
    shopcard.h \
    shovel.h \
    snowpea.h \
    tower.h \
    trashzombie.h \
    wallnut.h \
    way.h \
    words.h

FORMS += \
    choosesave.ui \
    game.ui \
    help.ui \
    mainwindow.ui \
    maps.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
