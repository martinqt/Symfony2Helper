#include "composerwindow.h"

ComposerWindow::ComposerWindow(QObject *parent) :
    BaseWindow(parent) {
    _ready = false;
}

bool ComposerWindow::isReady() {
    return _ready;
}

void ComposerWindow::process(QString workingDir, QString consolePath) {
    model = new CommandModel(workingDir, consolePath, this);
    connect(model, SIGNAL(populated()), this, SLOT(loadQML()));
    model->startProcess();
}

void ComposerWindow::loadQML() {
    engine->rootContext()->setContextProperty("commandModel",model);
    this->loadFile("composer");
    _ready = true;
    emit ready();
}
