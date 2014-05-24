#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QMap>
#include "basewindow.h"
#include "commandwindow.h"

class MainWindow : public BaseWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QObject *parent = 0);
        void setExePath(QString path);
        QMap<QString, QString> getParameters();

    public slots:
        void displayConsole();
        bool isConsoleReady();

    signals:
        void consoleReady();

    private slots:
        void emitConsoleReady();

    private:
        void loadConfig();

        CommandWindow *console;
        QMap<QString, QString> parameters;
};

#endif // MAINWINDOW_H
