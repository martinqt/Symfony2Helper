#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>
#include "commandmodel.h"
#include "commandwindow.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QString exePath = app.applicationDirPath();
    QDir work = QDir(exePath);
    work.cd("../");
    QDir console = QDir(exePath);
    console.cd("../app");

    CommandWindow *comWin = new CommandWindow();
    comWin->process(work.absolutePath(), console.absoluteFilePath("console"));

    return app.exec();
}
