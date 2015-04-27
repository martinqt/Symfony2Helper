#ifndef COMPOSERWINDOW_H
#define COMPOSERWINDOW_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QObject>
#include <QQmlContext>
#include "basewindow.h"
#include "commandmodel.h"

class ComposerWindow : public BaseWindow {

    Q_OBJECT

    public:
        ComposerWindow(QObject *parent = 0);
        bool isReady();

    public slots:
        void process(QString workingDir, QString consolePath);
        void loadQML();

    signals:
        void ready();

    private:
        CommandModel *model;
        bool _ready;
};

#endif // COMMANDWINDOW_H
