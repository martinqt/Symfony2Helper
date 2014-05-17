#include <QGuiApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    MainWindow *window = new MainWindow();
    window->setExePath(app.applicationDirPath());

    window->showWindow();

    return app.exec();
}
