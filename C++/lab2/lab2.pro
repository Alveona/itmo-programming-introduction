QT += widgets


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
TARGET = lab2
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    mainwindow.cpp \
    rbbutton.cpp \
    logicbutton.cpp

HEADERS += \
    mainwindow.h \
    rbbutton.h \
    logicbutton.h

DISTFILES += \
    Assets/digital-7.ttf \
    Assets/cell.png \
    Assets/cell_0.png \
    Assets/cell_1.png \
    Assets/cell_2.png \
    Assets/cell_3.png \
    Assets/cell_4.png \
    Assets/cell_5.png \
    Assets/counter_background.png \
    Assets/flag.png \
    Assets/game_button.png \
    Assets/mine.png \
    Assets/cell.png

RESOURCES += \
    resources.qrc
