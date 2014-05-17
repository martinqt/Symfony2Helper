#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
#include "basewindow.h"
#include "commandwindow.h"
#include "splashscreen.h"

class MainWindow : public BaseWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QObject *parent = 0);
        void setExePath(QString path);

    public slots:
        void displayConsole();
        void showSplashScreen();
        void hideSplashScreen();

    signals:
        void consoleReady();

    private:
        void loadConfig();

        CommandWindow *console;
        //SplashScreen *splash;
        QString workingDir, consolePath, exePath;
};

#endif // MAINWINDOW_H
