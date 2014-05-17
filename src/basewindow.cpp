#include "basewindow.h"

BaseWindow::BaseWindow(QObject *parent) :
    QObject(parent) {
    engine = new QQmlApplicationEngine(this);
}

void BaseWindow::showWindow() {
    if(window->isVisible() == false) {
        window->show();
    }
}

void BaseWindow::hideWindow() {
    if(window->isVisible() == true) {
        window->hide();
    }
}

void BaseWindow::loadFile(QString name) {
    engine->load(QUrl("qrc:/qml/"+name));
    this->storeWindow();
}

void BaseWindow::storeWindow() {
    QObject *topLevel = engine->rootObjects().value(0);
    window = qobject_cast<QQuickWindow *>(topLevel);
}
