QT += qml quick widgets xml

CONFIG += console

TARGET = gallery

SOURCES += \
    src/main.cpp \
    src/commandmodel.cpp

OTHER_FILES += \
    main.qml

RESOURCES += \
    resources.qrc

HEADERS += \
    src/commandmodel.h
