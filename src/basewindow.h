#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QString>

class BaseWindow : public QObject {

    Q_OBJECT

    public:
        explicit BaseWindow(QObject *parent = 0);

    public slots:
        void showWindow();
        void hideWindow();
        void loadFile(QString name);

    protected:
        void storeWindow();

        QQmlApplicationEngine *engine;
        QQuickWindow *window;
};

#endif // BASEWINDOW_H
