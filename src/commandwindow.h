#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QObject>
#include <QQmlContext>
#include "commandmodel.h"

class CommandWindow : public QObject {

    Q_OBJECT

    public:
        CommandWindow(QObject *parent = 0);

    public slots:
        void process(QString workingDir, QString consolePath);
        void loadQML();

    private:
        QQmlApplicationEngine *engine;
        CommandModel *model;
};

#endif // COMMANDWINDOW_H
