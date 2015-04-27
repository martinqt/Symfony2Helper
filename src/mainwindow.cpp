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
    parameters["exePath"] = path;
    this->loadConfig();
    console->process(parameters["workingDir"], parameters["consolePath"]);
    composer->process(parameters["workingDir"], parameters["composerPath"]);
}

QMap<QString, QString> MainWindow::getParameters() {
    return parameters;
}

void MainWindow::loadConfig() {
    QSettings settings("config.ini", QSettings::IniFormat);
    parameters["workingDir"] = settings.value("Locations/work", "default").toString();
    parameters["consolePath"] = settings.value("Locations/console", "default").toString();
    parameters["composerPath"] = settings.value("Locations/composer", "default").toString();


    if(parameters["workingDir"] == "default") {
        QDir workDir = QDir(parameters["exePath"]);
        workDir.cd("../");
        parameters["workingDir"] = workDir.absolutePath();
    }

    if(parameters["consolePath"] == "default") {
        QDir consoleDir = QDir(parameters["exePath"]);
        consoleDir.cd("../app");
        parameters["consolePath"] = consoleDir.absoluteFilePath("console");
    }

    if(parameters["composerPath"] == "default") {
        QDir consoleDir = QDir(parameters["exePath"]);
        consoleDir.cd("../");
        parameters["composerPath"] = consoleDir.absoluteFilePath("composer.phar");
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
