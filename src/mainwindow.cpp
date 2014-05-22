#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) :
    BaseWindow(parent) {
    console = new CommandWindow(this);
    connect(console, SIGNAL(ready()), this, SLOT(emitConsoleReady()));

    composer = new ComposerWindow(this);
    connect(composer, SIGNAL(ready()), this, SLOT(emitComposerReady()));

    engine->rootContext()->setContextProperty("cpp",this);
    this->loadFile("main");
}

void MainWindow::setExePath(QString path) {
    exePath = path;
    this->loadConfig();
    console->process(workingDir, consolePath);
    composer->process(workingDir, composerPath);
}

void MainWindow::loadConfig() {
    QSettings settings("config.ini", QSettings::IniFormat);
    workingDir = settings.value("Directories/work", "default").toString();
    consolePath = settings.value("Directories/console", "default").toString();
    composerPath = settings.value("Directories/composer", "default").toString();

    if(workingDir == "default") {
        QDir workDir = QDir(exePath);
        workDir.cd("../");
        workingDir = workDir.absolutePath();
    }

    if(consolePath == "default") {
        QDir consoleDir = QDir(exePath);
        consoleDir.cd("../app");
        consolePath = consoleDir.absoluteFilePath("console");
    }

    if(composerPath == "default") {
        QDir consoleDir = QDir(exePath);
        consoleDir.cd("../");
        consolePath = consoleDir.absoluteFilePath("composer.phar");
    }
}

void MainWindow::emitConsoleReady() {
    emit consoleReady();
}

void MainWindow::emitComposerReady() {
    emit composerReady();
}

void MainWindow::displayConsole() {
    if(console->isReady()) {
        console->showWindow();
    }
}

void MainWindow::displayComposer() {
    if(composer->isReady()) {
        composer->showWindow();
    }
}

bool MainWindow::isConsoleReady() {
    return console->isReady();
}

bool MainWindow::isComposerReady() {
    return composer->isReady();
}
