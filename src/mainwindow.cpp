#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) :
    BaseWindow(parent) {
    console = new CommandWindow(this);
    //splash = new SplashScreen(this);

    engine->rootContext()->setContextProperty("cpp",this);
    this->loadFile("main");

    //connect(console, SIGNAL(hideSplash()), this, SLOT(hideSplashScreen()));
}

void MainWindow::setExePath(QString path) {
    exePath = path;
    this->loadConfig();
    console->process(workingDir, consolePath);
}

void MainWindow::loadConfig() {
    QSettings settings("config.ini", QSettings::IniFormat);
    workingDir = settings.value("Directories/work", "default").toString();
    consolePath = settings.value("Directories/console", "default").toString();

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
}

void MainWindow::showSplashScreen() {
    //this->splash->showWindow();
}

void MainWindow::hideSplashScreen() {
    //this->splash->hideWindow();
}

void MainWindow::displayConsole() {
    //this->showSplashScreen();
    console->showWindow();
}
