#include "commandwindow.h"

CommandWindow::CommandWindow(QObject *parent) :
    BaseWindow(parent) {
    _ready = false;
}

bool CommandWindow::isReady() {
    return _ready;
}

void CommandWindow::process(QString workingDir, QString consolePath) {
    model = new CommandModel(workingDir, consolePath, this);
    connect(model, SIGNAL(populated()), this, SLOT(loadQML()));
    model->startProcess();
}

void CommandWindow::loadQML() {
    engine->rootContext()->setContextProperty("commandModel",model);
    this->loadFile("console");
    _ready = true;
    emit ready();
}
