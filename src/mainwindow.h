#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
#include "basewindow.h"
#include "commandwindow.h"
#include "composerwindow.h"

class MainWindow : public BaseWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QObject *parent = 0);
        void setExePath(QString path);

    public slots:
        void displayConsole();
        bool isConsoleReady();

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
        QString workingDir, consolePath, exePath;
};

#endif // MAINWINDOW_H
