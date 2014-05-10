#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>
#include "commandmodel.h"
#include "commandwindow.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    CommandWindow *comWin = new CommandWindow();
    comWin->process("C:/wamp/www/SWTOR", "C:/wamp/www/SWTOR/app/console");

    return app.exec();
}
