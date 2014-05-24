#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QMap>
#include "basewindow.h"
#include "commandwindow.h"
#include "composerwindow.h"

class MainWindow : public BaseWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QObject *parent = 0);
        void setExePath(QString path);
        QMap<QString, QString> getParameters();

    public slots:
        void displayConsole();
        void displayComposer();
        bool isConsoleReady();
        bool isComposerReady();

    signals:
        void consoleReady();
        void composerReady();

    private slots:
        void emitConsoleReady();
        void emitComposerReady();

    private:
        void loadConfig();

        CommandWindow *console;
        ComposerWindow *composer;
        QString composerPath;
        QMap<QString, QString> parameters;
};

#endif // MAINWINDOW_H
