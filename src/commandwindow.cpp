#include "commandwindow.h"

CommandWindow::CommandWindow(QObject *parent) :
    QObject(parent) {
    engine = new QQmlApplicationEngine(this);
}

void CommandWindow::process(QString workingDir, QString consolePath) {
    model = new CommandModel(workingDir, consolePath, this);
    connect(model, SIGNAL(populated()), this, SLOT(loadQML()));
    model->startProcess();
}

void CommandWindow::loadQML() {
    engine->rootContext()->setContextProperty("commandModel",model);
    engine->load(QUrl("qrc:/console.qml"));

    QObject *topLevel = engine->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->show();
}
