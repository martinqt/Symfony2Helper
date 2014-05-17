QT += qml quick widgets xml

CONFIG += console

TARGET = Sf2Helper

SOURCES += \
    src/main.cpp \
    src/commandmodel.cpp \
    src/commandwindow.cpp \
    src/mainwindow.cpp \
    src/basewindow.cpp

OTHER_FILES += \
    qml/main.qml \
    qml/Console.qml

RESOURCES += \
    resources.qrc

HEADERS += \
    src/commandmodel.h \
    src/commandwindow.h \
    src/mainwindow.h \
    src/basewindow.h
