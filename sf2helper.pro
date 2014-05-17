QT += qml quick widgets xml

CONFIG += console

TARGET = Sf2Helper

SOURCES += \
    src/main.cpp \
    src/commandmodel.cpp \
    src/commandwindow.cpp

OTHER_FILES += \
    qml/console.qml

RESOURCES += \
    resources.qrc

HEADERS += \
    src/commandmodel.h \
    src/commandwindow.h
