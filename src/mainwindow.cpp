#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) :
    BaseWindow(parent) {
    console = new CommandWindow(this);
    connect(console, SIGNAL(ready()), this, SLOT(emitConsoleReady()));

    engine->rootContext()->setContextProperty("cpp",this);
    this->loadFile("main");
}

void MainWindow::setExePath(QString path) {
    parameters["exePath"] = path;
    this->loadConfig();
    console->process(parameters["workingDir"], parameters["consolePath"]);
}

QMap<QString, QString> MainWindow::getParameters() {
    return parameters;
}

void MainWindow::loadConfig() {
    QSettings settings("config.ini", QSettings::IniFormat);
    parameters["workingDir"] = settings.value("Locations/work", "default").toString();
    parameters["consolePath"] = settings.value("Locations/console", "default").toString();

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
}

void MainWindow::emitConsoleReady() {
    emit consoleReady();
}

void MainWindow::displayConsole() {
    if(console->isReady()) {
        console->showWindow();
    }
}

bool MainWindow::isConsoleReady() {
    return console->isReady();
}
