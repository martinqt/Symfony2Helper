#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>
#include <QSettings>
#include "commandmodel.h"
#include "commandwindow.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QSettings settings("config.ini", QSettings::IniFormat);
    QString work = settings.value("Directories/work", "default").toString();
    QString console = settings.value("Directories/console", "default").toString();

    if(work == "default") {
        QString exePath = app.applicationDirPath();
        QDir workDir = QDir(exePath);
        workDir.cd("../");
        work = workDir.absolutePath();
    }
    if(console == "default") {
        QString exePath = app.applicationDirPath();
        QDir consoleDir = QDir(exePath);
        consoleDir.cd("../app");
        console = consoleDir.absoluteFilePath("console");
    }

    CommandWindow *comWin = new CommandWindow();
    comWin->process(work, console);

    return app.exec();
}
